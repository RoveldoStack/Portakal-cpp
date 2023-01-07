#include "DX12CommandBuffer.h"
#include <Runtime/DX12/DX12DeviceObjects.h>
#include <Runtime/DXGI/DXGIUtils.h>
#include <Runtime/DX12/DX12Device.h>
#include <Runtime/Assert/Assert.h>

namespace Portakal
{
    DX12CommandBuffer::DX12CommandBuffer(const CommandBufferCreateDesc& desc, DX12Device* pDevice) : CommandBuffer(desc)
    {
        ID3D12Device* pDX12Device = pDevice->GetDXDevice();
        ID3D12CommandAllocator* pOwnerAllocator = pDevice->GetDXCmdAllocator();

        ASSERT(SUCCEEDED(pDX12Device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, pOwnerAllocator, nullptr, IID_PPV_ARGS(&_cmdList))), "DX12CommandBuffer", "Failed to create a command list!");

        ASSERT(SUCCEEDED(_cmdList->Close()), "DX12CommandBuffer", "Failed to close the command list");

        _ownerAllocator = pOwnerAllocator;
    }
    DX12CommandBuffer::~DX12CommandBuffer()
    {
        _ownerAllocator = nullptr;
        _cmdList.Reset();
    }
    void DX12CommandBuffer::LockCore()
    {
        ASSERT(SUCCEEDED(_cmdList->Reset(_ownerAllocator, nullptr)), "DX12CommandBuffer", "Failed to reset the command buffer");
    }
    void DX12CommandBuffer::UnlockCore()
    {
        /*
        * Validate if a framebuffer still attached and barrier
        */
        Framebuffer* pFramebuffer = GetBoundFramebuffer();
        if (pFramebuffer != nullptr)
        {
            if (pFramebuffer->IsSwapchain())
            {
                ID3D12Resource* pResource = ((DX12Texture*)pFramebuffer->GetColorTargets()[0])->GetDXTexture();

                D3D12_RESOURCE_BARRIER barrier = {};
                barrier.Transition.pResource = pResource;
                barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
                barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;
                barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
                barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
                barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
                _cmdList->ResourceBarrier(1, &barrier);
            }
            else
            {
                const DX12Framebuffer* pDXFramebuffer = (const DX12Framebuffer*)pFramebuffer;
                const Array<Texture*> attachments = pDXFramebuffer->GetColorTargets();
                for (unsigned int i = 0; i < attachments.GetCursor(); i++)
                {
                    D3D12_RESOURCE_BARRIER barrier = {};
                    barrier.Transition.pResource = ((const DX12Texture*)attachments[i])->GetDXTexture();
                    barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
                    barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_COPY_DEST;
                    barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
                    barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
                    barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
                    _cmdList->ResourceBarrier(1, &barrier);
                }
            }
        }

        ASSERT(SUCCEEDED(_cmdList->Close()), "DX12CommandBuffer", "Failed to close the command list");
    }
    void DX12CommandBuffer::BindPipelineCore(Pipeline* pPipeline)
    {
        const DX12Pipeline* pDXPipeline = (const DX12Pipeline*)pPipeline;

        _cmdList->SetGraphicsRootSignature(pDXPipeline->GetDXRootSignature());
        _cmdList->SetPipelineState(pDXPipeline->GetDXPipelineState());
        _cmdList->IASetPrimitiveTopology(pDXPipeline->GetDXTopology());
    }
    void DX12CommandBuffer::BindFramebufferCore(Framebuffer* pFramebuffer)
    {
        /*
        * Validate if a framebuffer still attached
        */
        Framebuffer* pCurrentFramebuffer = GetBoundFramebuffer();
        if (pCurrentFramebuffer != nullptr)
        {
            if (pCurrentFramebuffer->IsSwapchain())
            {
                const DX12SwapchainFramebuffer* pDXFramebuffer = (const DX12SwapchainFramebuffer*)pFramebuffer;
                const Texture* pTexture = pFramebuffer->GetColorTargets()[0];
                ID3D12Resource* pResource = ((DX12Texture*)pTexture)->GetDXTexture();

                D3D12_RESOURCE_BARRIER barrier = {};
                barrier.Transition.pResource = pResource;
                barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
                barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;
                barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
                barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
                barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;

                _cmdList->ResourceBarrier(1, &barrier);
            }
            else
            {
                const DX12Framebuffer* pDXFramebuffer = (const DX12Framebuffer*)pCurrentFramebuffer;
                const Array<Texture*> attachments = pDXFramebuffer->GetColorTargets();

                for (unsigned int i = 0; i < attachments.GetCursor(); i++)
                {
                    D3D12_RESOURCE_BARRIER barrier = {};
                    barrier.Transition.pResource = ((const DX12Texture*)attachments[i])->GetDXTexture();
                    barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
                    barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_COPY_DEST;
                    barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
                    barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
                    barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
                    _cmdList->ResourceBarrier(1, &barrier);
                }
            }
        }

        /*
        * Validate if swapchain
        */
        D3D12_CPU_DESCRIPTOR_HANDLE renderTargetDescriptor = {};
        unsigned int attachmentCount = 1;
        if (pFramebuffer->IsSwapchain())
        {
            const DX12SwapchainFramebuffer* pDXFramebuffer = (const DX12SwapchainFramebuffer*)pFramebuffer;
            const Texture* pTexture = pFramebuffer->GetColorTargets()[0];
            ID3D12Resource* pResource = ((DX12Texture*)pTexture)->GetDXTexture();

            D3D12_RESOURCE_BARRIER barrier = {};
            barrier.Transition.pResource = pResource;
            barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;
            barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;
            barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
            barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
            barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;

            _cmdList->ResourceBarrier(1, &barrier);

            renderTargetDescriptor = pDXFramebuffer->GetDXCurrentRenderTargetDescriptor();
        }
        else
        {
            const DX12Framebuffer* pDXFramebuffer = (const DX12Framebuffer*)pFramebuffer;
            const Array<Texture*> attachments = pDXFramebuffer->GetColorTargets();
            for (unsigned int i = 0; i < attachments.GetCursor(); i++)
            {
                D3D12_RESOURCE_BARRIER barrier = {};
                barrier.Transition.pResource = ((const DX12Texture*)attachments[i])->GetDXTexture();
                barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_COPY_DEST;
                barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;
                barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
                barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
                barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
                _cmdList->ResourceBarrier(1, &barrier);
            }

            renderTargetDescriptor = pDXFramebuffer->GetDXColorHeapDescriptor()->GetCPUDescriptorHandleForHeapStart();
            attachmentCount = attachments.GetCursor();
        }

        _cmdList->OMSetRenderTargets(attachmentCount, &renderTargetDescriptor, true, nullptr);
    }
    void DX12CommandBuffer::SetViewportsCore(const Array<ViewportDesc>& viewports)
    {
        Array<D3D12_VIEWPORT> dxViewports;
        for (unsigned int i = 0; i < viewports.GetCursor(); i++)
        {
            const ViewportDesc& viewportDesc = viewports[i];
            D3D12_VIEWPORT viewport = {};
            viewport.TopLeftX = viewportDesc.X;
            viewport.TopLeftY = viewportDesc.Y;
            viewport.Width = viewportDesc.Width;
            viewport.Height = viewportDesc.Height;
            viewport.MinDepth = viewportDesc.MinDepth;
            viewport.MaxDepth = viewportDesc.MaxDepth;

            dxViewports.Add(viewport);
        }

        _cmdList->RSSetViewports(dxViewports.GetCursor(), dxViewports.GetData());
    }
    void DX12CommandBuffer::SetScissorsCore(const Array<ScissorDesc>& scissors)
    {
        Array<D3D12_RECT> dxScissors;
        for (unsigned int i = 0; i < scissors.GetCursor(); i++)
        {
            const ScissorDesc& scissorDesc = scissors[i];
            D3D12_RECT rect = {};
            rect.left = 0;
            rect.top = 0;
            rect.right = scissorDesc.Width - scissorDesc.X;
            rect.bottom = scissorDesc.Height - scissorDesc.Y;

            dxScissors.Add(rect);
        }

        _cmdList->RSSetScissorRects(dxScissors.GetCursor(), dxScissors.GetData());
    }
    void DX12CommandBuffer::ClearColorCore(const float r, const float g, const float b, const float a)
    {
        const float clearColor[] = { r,g,b,a };

        const Framebuffer* pFramebuffer = GetBoundFramebuffer();

        if (pFramebuffer->IsSwapchain())
        {
            const DX12SwapchainFramebuffer* pDXFramebuffer = (const DX12SwapchainFramebuffer*)pFramebuffer;

            D3D12_CPU_DESCRIPTOR_HANDLE renderTargetDescriptorHandle = {};
            renderTargetDescriptorHandle = pDXFramebuffer->GetDXCurrentRenderTargetDescriptor();

            _cmdList->ClearRenderTargetView(renderTargetDescriptorHandle, clearColor, 0, nullptr);
        }
        else
        {
            const DX12Framebuffer* pDXFramebuffer = (const DX12Framebuffer*)pFramebuffer;

            D3D12_CPU_DESCRIPTOR_HANDLE renderTargetDescriptorHandle = {};
            renderTargetDescriptorHandle = pDXFramebuffer->GetDXColorHeapDescriptor()->GetCPUDescriptorHandleForHeapStart();

            const unsigned int rtvIncrementSize = ((const DX12Device*)GetOwnerDevice())->GetDXDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
            Array<Texture*> colorAttachments = pDXFramebuffer->GetColorTargets();
            for (unsigned int i = 0; i < colorAttachments.GetCursor(); i++)
            {
                _cmdList->ClearRenderTargetView(renderTargetDescriptorHandle, clearColor, 0, nullptr);
                renderTargetDescriptorHandle.ptr += rtvIncrementSize;
            }

        }
    }
    void DX12CommandBuffer::ClearDepthCore(const float depth)
    {
        const Framebuffer* pFramebuffer = GetBoundFramebuffer();

        D3D12_CPU_DESCRIPTOR_HANDLE cpuHandle = {};
        if (pFramebuffer->IsSwapchain())
        {
            
        }
        else
        {

        }

        _cmdList->ClearDepthStencilView(cpuHandle, D3D12_CLEAR_FLAG_DEPTH, depth, 0, 0, nullptr);
    }
    void DX12CommandBuffer::ClearStencilCore(const int stencil)
    {
        const Framebuffer* pFramebuffer = GetBoundFramebuffer();

        D3D12_CPU_DESCRIPTOR_HANDLE cpuHandle = {};
        if (pFramebuffer->IsSwapchain())
        {

        }
        else
        {

        }

        _cmdList->ClearDepthStencilView(cpuHandle, D3D12_CLEAR_FLAG_STENCIL, 0,stencil, 0, nullptr);
    }
    void DX12CommandBuffer::SetVertexBufferCore(GraphicsBuffer* pBuffer)
    {
        const DX12Buffer* pDXBuffer = (const DX12Buffer*)pBuffer;
        const D3D12_VERTEX_BUFFER_VIEW bufferView = pDXBuffer->GetDXVertexBufferView();

        _cmdList->IASetVertexBuffers(0, 1, &bufferView);
    }
    void DX12CommandBuffer::SetIndexBufferCore(GraphicsBuffer* pBuffer)
    {
        const DX12Buffer* pDXBuffer = (const DX12Buffer*)pBuffer;
        const D3D12_INDEX_BUFFER_VIEW bufferView = pDXBuffer->GetDXIndexBufferView();

        _cmdList->IASetIndexBuffer(&bufferView);
    }
    void DX12CommandBuffer::CommitResourceTableCore(const unsigned int slotIndex, const GraphicsResourceTable* pTable)
    {
        const DX12ResourceTable* pDXTable = (const DX12ResourceTable*)pTable;
        ID3D12DescriptorHeap* pDescriptorHeap = pDXTable->GetDXDescriptorHeap();

        _cmdList->SetDescriptorHeaps(1, &pDescriptorHeap);
        _cmdList->SetGraphicsRootDescriptorTable(slotIndex, pDescriptorHeap->GetGPUDescriptorHandleForHeapStart());

    }
    void DX12CommandBuffer::DrawIndexedCore(const unsigned int indexCount)
    {
        _cmdList->DrawIndexedInstanced(indexCount, 1, 0, 0, 0);
    }
    void DX12CommandBuffer::UpdateBufferCore(const GraphicsBufferUpdateDesc& desc, GraphicsBuffer* pBuffer)
    {
    }
    void DX12CommandBuffer::UpdateTextureCore(const TextureUpdateDesc& desc, Texture* pTexture)
    {

    }
    void DX12CommandBuffer::ClearCachedStateCore()
    {
    }
}