#include "DX12GraphicsCommandList.h"
#include <Runtime/DX12/DX12DeviceObjects.h>
#include <Runtime/DXGI/DXGIUtils.h>
#include <Runtime/DX12/DX12Device.h>
#include <Runtime/Assert/Assert.h>
#include <Runtime/Memory/Memory.h>
#include <Runtime/Graphics/TextureUtils.h>
#include <d3d11.h>
namespace Portakal
{
    DX12GraphicsCommandList::DX12GraphicsCommandList(const CommandListCreateDesc& desc, DX12Device* pDevice) : CommandList(desc,CommandQueueType::Graphics)
    {
        ID3D12Device* pDX12Device = pDevice->GetDXDevice();
        ID3D12CommandAllocator* pOwnerAllocator = pDevice->GetDXGraphicsCmdAllocator();

        ASSERT(SUCCEEDED(pDX12Device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, pOwnerAllocator, nullptr, IID_PPV_ARGS(&mCmdList))), "DX12CommandList", "Failed to create a command list!");

        ASSERT(SUCCEEDED(mCmdList->Close()), "DX12CommandList", "Failed to close the command list");

        mAllocator = pOwnerAllocator;
    }
    DX12GraphicsCommandList::~DX12GraphicsCommandList()
    {
        mAllocator = nullptr;
        mCmdList.Reset();
    }
    void DX12GraphicsCommandList::LockCore()
    {

        ASSERT(SUCCEEDED(mCmdList->Reset(mAllocator, nullptr)), "DX12CommandList", "Failed to reset the command buffer");
    }
    void DX12GraphicsCommandList::UnlockCore()
    {
        /*
        * Validate if a framebuffer still attached and barrier
        */
        Framebuffer* pFramebuffer = GetBoundFramebuffer();
        if (pFramebuffer != nullptr)
            FreeFormerFramebufferBarriers();
        
        ASSERT(SUCCEEDED(mCmdList->Close()), "DX12CommandList", "Failed to close the command list");
    }
    void DX12GraphicsCommandList::BindPipelineCore(Pipeline* pPipeline)
    {
        const DX12GraphicsPipeline* pDXPipeline = (const DX12GraphicsPipeline*)pPipeline;

        mCmdList->SetGraphicsRootSignature(pDXPipeline->GetDXRootSignature());
        mCmdList->SetPipelineState(pDXPipeline->GetDXPipelineState());
        mCmdList->IASetPrimitiveTopology(pDXPipeline->GetDXTopology());
    }
    void DX12GraphicsCommandList::BindFramebufferCore(Framebuffer* pFramebuffer)
    {
        ID3D12Device* pDevice = ((DX12Device*)GetOwnerDevice())->GetDXDevice();

        Framebuffer* pCurrentFramebuffer = GetBoundFramebuffer();

        if (pCurrentFramebuffer == pFramebuffer)
            return;

        /*
        * Free the former framebuffer barries
        */
        if (pCurrentFramebuffer != nullptr)
            FreeFormerFramebufferBarriers();

        /*
        * Validate if swapchain
        */
        if (pFramebuffer == nullptr)
            return;

        if (pFramebuffer->IsSwapchain())
        {
            const Swapchain* pSwapchain = GetOwnerDevice()->GetSwapchain();
            const DX12Framebuffer* pDXFramebuffer = (const DX12Framebuffer*)pFramebuffer;
            DX12Texture* pColorTarget = ((DX12Texture*)pDXFramebuffer->GetColorTargets()[pSwapchain->GetCurrentImageIndex()].pTexture);
            DX12Texture* pDepthTarget = (DX12Texture*)pDXFramebuffer->GetDepthStencilTarget().pTexture;

            Array<D3D12_RESOURCE_BARRIER> barriers;

            //Color barriers
            D3D12_RESOURCE_BARRIER colorBarrier = {};
            colorBarrier.Transition.pResource = pColorTarget->GetDXTexture();
            colorBarrier.Transition.StateBefore = pColorTarget->GetDXResourceState();
            colorBarrier.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;
            colorBarrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
            colorBarrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
            colorBarrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;

            barriers.Add(colorBarrier);

            pColorTarget->MutateDXResourceState(D3D12_RESOURCE_STATE_RENDER_TARGET);

            //Depth barriers
            if (pDepthTarget != nullptr)
            {
                D3D12_RESOURCE_BARRIER depthBarrier = {};
                depthBarrier.Transition.pResource = pDepthTarget->GetDXTexture();
                depthBarrier.Transition.StateBefore = pDepthTarget->GetDXResourceState();
                depthBarrier.Transition.StateAfter = D3D12_RESOURCE_STATE_DEPTH_WRITE;
                depthBarrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
                depthBarrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
                depthBarrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;

                barriers.Add(depthBarrier);

                pDepthTarget->MutateDXResourceState(D3D12_RESOURCE_STATE_DEPTH_WRITE);
            }

            mCmdList->ResourceBarrier(barriers.GetCursor(), barriers.GetData());

            D3D12_CPU_DESCRIPTOR_HANDLE colorHandle = pDXFramebuffer->GetDXColorHeapDescriptor()->GetCPUDescriptorHandleForHeapStart();
            colorHandle.ptr += pSwapchain->GetCurrentImageIndex() * pDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);


            mCmdList->OMSetRenderTargets(1, &colorHandle, true, nullptr);
        }
        else
        {
            const DX12Framebuffer* pDXFramebuffer = (const DX12Framebuffer*)pFramebuffer;
            const Array<FramebufferAttachmentDesc> colorAttachments = pFramebuffer->GetColorTargets();
            DX12Texture* const pDepthTarget = (DX12Texture*)pFramebuffer->GetDepthStencilTarget().pTexture;

            Array<D3D12_RESOURCE_BARRIER> barriers;

            //Barrier colors
            for (unsigned int i = 0; i < colorAttachments.GetCursor(); i++)
            {
                DX12Texture* const pColorTarget = (DX12Texture*)colorAttachments[i].pTexture;

                D3D12_RESOURCE_BARRIER barrier = {};
                barrier.Transition.pResource = pColorTarget->GetDXTexture();
                barrier.Transition.StateBefore = pColorTarget->GetDXResourceState();
                barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;
                barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
                barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
                barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;

                barriers.Add(barrier);

                pColorTarget->MutateDXResourceState(D3D12_RESOURCE_STATE_RENDER_TARGET);
            }

            //Barrier depth stencil
            if (pDepthTarget != nullptr)
            {
                D3D12_RESOURCE_BARRIER barrier = {};
                barrier.Transition.pResource = pDepthTarget->GetDXTexture();
                barrier.Transition.StateBefore = pDepthTarget->GetDXResourceState();
                barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_DEPTH_WRITE;
                barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
                barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
                barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;

                barriers.Add(barrier);

                pDepthTarget->MutateDXResourceState(D3D12_RESOURCE_STATE_DEPTH_WRITE);
            }

            mCmdList->ResourceBarrier(barriers.GetCursor(), barriers.GetData());

            D3D12_CPU_DESCRIPTOR_HANDLE colorHandle = pDXFramebuffer->GetDXColorHeapDescriptor()->GetCPUDescriptorHandleForHeapStart();


            mCmdList->OMSetRenderTargets(colorAttachments.GetCursor(), &colorHandle, true, nullptr);
        }

    }
    void DX12GraphicsCommandList::SetViewportsCore(const Array<ViewportDesc>& viewports)
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

        mCmdList->RSSetViewports(dxViewports.GetCursor(), dxViewports.GetData());
    }
    void DX12GraphicsCommandList::SetScissorsCore(const Array<ScissorDesc>& scissors)
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

        mCmdList->RSSetScissorRects(dxScissors.GetCursor(), dxScissors.GetData());
    }
    void DX12GraphicsCommandList::ClearColorCore(const unsigned int index,const ColorRgba& color)
    {
        const DX12Framebuffer* pFramebuffer = (const DX12Framebuffer*)GetBoundFramebuffer();
        if (pFramebuffer == nullptr)
            return;

        const float clearColor[] = { color.R/255.0f,color.G/255.0f,color.B/255.0f,color.A/255.0f };
        const DX12Device* pDevice = (const DX12Device*)GetOwnerDevice();
        const Swapchain* pSwapchain = pDevice->GetSwapchain();
        const unsigned int handleIncrementSize = pDevice->GetDXDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
        D3D12_CPU_DESCRIPTOR_HANDLE cpuHandle = pFramebuffer->GetDXColorHeapDescriptor()->GetCPUDescriptorHandleForHeapStart();

        if (pFramebuffer->IsSwapchain())
        {
            cpuHandle.ptr += pSwapchain->GetCurrentImageIndex() * handleIncrementSize;
        }
        else
        {
            cpuHandle.ptr + index * handleIncrementSize;
        }

        mCmdList->ClearRenderTargetView(cpuHandle, clearColor, 0, nullptr);

    }

    void DX12GraphicsCommandList::ClearColorCore(const unsigned int index, const ColorRgbaF& color)
    {
        const DX12Framebuffer* pFramebuffer = (const DX12Framebuffer*)GetBoundFramebuffer();
        if (pFramebuffer == nullptr)
            return;

        const DX12Device* pDevice = (const DX12Device*)GetOwnerDevice();
        const Swapchain* pSwapchain = pDevice->GetSwapchain();
        const unsigned int handleIncrementSize = pDevice->GetDXDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
        D3D12_CPU_DESCRIPTOR_HANDLE cpuHandle = pFramebuffer->GetDXColorHeapDescriptor()->GetCPUDescriptorHandleForHeapStart();

        if (pFramebuffer->IsSwapchain())
        {
            cpuHandle.ptr += pSwapchain->GetCurrentImageIndex() * handleIncrementSize;
        }
        else
        {
            cpuHandle.ptr + index * handleIncrementSize;
        }

        mCmdList->ClearRenderTargetView(cpuHandle, &color.R, 0, nullptr);

    }
    void DX12GraphicsCommandList::ClearDepthCore(const float depth)
    {
        const Framebuffer* pFramebuffer = GetBoundFramebuffer();

        D3D12_CPU_DESCRIPTOR_HANDLE cpuHandle = ((const DX12Framebuffer*)pFramebuffer)->GetDXDepthStencilHeapDescriptor()->GetCPUDescriptorHandleForHeapStart();

        mCmdList->ClearDepthStencilView(cpuHandle, D3D12_CLEAR_FLAG_DEPTH, depth, 0, 0, nullptr);
    }
    void DX12GraphicsCommandList::ClearStencilCore(const int stencil)
    {
        const Framebuffer* pFramebuffer = GetBoundFramebuffer();

        D3D12_CPU_DESCRIPTOR_HANDLE cpuHandle = ((const DX12Framebuffer*)pFramebuffer)->GetDXDepthStencilHeapDescriptor()->GetCPUDescriptorHandleForHeapStart();

        mCmdList->ClearDepthStencilView(cpuHandle, D3D12_CLEAR_FLAG_STENCIL, 0,stencil, 0, nullptr);
    }
    void DX12GraphicsCommandList::SetVertexBufferCore(GraphicsBuffer* pBuffer)
    {
        const DX12Buffer* pDXBuffer = (const DX12Buffer*)pBuffer;
        const D3D12_VERTEX_BUFFER_VIEW bufferView = pDXBuffer->GetDXVertexBufferView();

        mCmdList->IASetVertexBuffers(0, 1, &bufferView);
    }
    void DX12GraphicsCommandList::SetIndexBufferCore(GraphicsBuffer* pBuffer)
    {
        const DX12Buffer* pDXBuffer = (const DX12Buffer*)pBuffer;
        const D3D12_INDEX_BUFFER_VIEW bufferView = pDXBuffer->GetDXIndexBufferView();

        mCmdList->IASetIndexBuffer(&bufferView);
    }
    void DX12GraphicsCommandList::CommitResourceTableCore(const unsigned int slotIndex, const ResourceTable* pTable)
    {
        const DX12ResourceTable* pDXTable = (const DX12ResourceTable*)pTable;
        ID3D12DescriptorHeap* pCbvSrvUavHeap = pDXTable->GetDXCbvSrvUavHeap();
        ID3D12DescriptorHeap* pSamplerHeap = pDXTable->GetDXSamplerHeap();

        Array<ID3D12DescriptorHeap*> heaps;
        if (pCbvSrvUavHeap != nullptr)
            heaps.Add(pCbvSrvUavHeap);
        if (pSamplerHeap != nullptr)
            heaps.Add(pSamplerHeap);

        if (heaps.GetCursor() == 0)
            return;

        mCmdList->SetDescriptorHeaps(heaps.GetCursor(), heaps.GetData());

        for (unsigned int i = 0; i < heaps.GetCursor(); i++)
        {
            mCmdList->SetGraphicsRootDescriptorTable(i, heaps[i]->GetGPUDescriptorHandleForHeapStart());
        }
    }
    void DX12GraphicsCommandList::DrawIndexedCore(const unsigned int indexCount)
    {
        mCmdList->DrawIndexedInstanced(indexCount, 1, 0, 0, 0);
    }
    void DX12GraphicsCommandList::UpdateBufferCore(const GraphicsBufferUpdateDesc& desc, GraphicsBuffer* pBuffer)
    {

    }
    void DX12GraphicsCommandList::UpdateTextureCore(const TextureUpdateDesc& desc, Texture* pTexture)
    {
        DX12Texture* pDXTexture = (DX12Texture*)pTexture;
        const D3D12_RESOURCE_DESC textureDesc = pDXTexture->GetDXTexture()->GetDesc();
        const DX12Device* pDevice = (const DX12Device*)GetOwnerDevice();

        unsigned long long textureUploadBufferSize = 0;
        D3D12_PLACED_SUBRESOURCE_FOOTPRINT textureSubResourceFootprint = {};

        pDevice->GetDXDevice()->GetCopyableFootprints(&textureDesc, 0, 1, 0, &textureSubResourceFootprint, nullptr, nullptr, &textureUploadBufferSize);

        /*
        * Create upload buffer
        */
        D3D12_HEAP_PROPERTIES uploadBufferHeapProperties = {};
        uploadBufferHeapProperties.Type = D3D12_HEAP_TYPE_UPLOAD;
        uploadBufferHeapProperties.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
        uploadBufferHeapProperties.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
        uploadBufferHeapProperties.CreationNodeMask = 0;
        uploadBufferHeapProperties.VisibleNodeMask = 0;

        D3D12_RESOURCE_DESC uploadBufferResourceDesc = {};
        uploadBufferResourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
        uploadBufferResourceDesc.Format = DXGI_FORMAT_UNKNOWN;
        uploadBufferResourceDesc.Width = textureUploadBufferSize;
        uploadBufferResourceDesc.Height = 1;
        uploadBufferResourceDesc.DepthOrArraySize = 1;
        uploadBufferResourceDesc.MipLevels = 1;
        uploadBufferResourceDesc.Alignment = 0;
        uploadBufferResourceDesc.Flags = D3D12_RESOURCE_FLAG_NONE;
        uploadBufferResourceDesc.SampleDesc = { 1,0 };
        uploadBufferResourceDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

        DXPTR<ID3D12Resource> uploadBuffer;
        ASSERT(SUCCEEDED(pDevice->GetDXDevice()->CreateCommittedResource(&uploadBufferHeapProperties, D3D12_HEAP_FLAG_NONE,
            &uploadBufferResourceDesc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&uploadBuffer))), "DX12GraphicsCommandList", "Failed to create upload buffer for texture updating!");

        /*
        * Upload buffer content
        */
        unsigned char* pUploadBufferData = nullptr;
        const unsigned char* pSourceData = desc.pData;
        const unsigned int textureRowPitch = TextureUtils::GetFormatSize(pTexture->GetTextureFormat()) * pTexture->GetWidth();
        const unsigned int textureSlicePitch = textureRowPitch * pTexture->GetHeight();

        uploadBuffer->Map(0, nullptr, (void**)&pUploadBufferData);
        for (unsigned int sliceIndex = 0; sliceIndex < textureSubResourceFootprint.Footprint.Depth; sliceIndex++)
        {
            unsigned char* pDestinationSlice = pUploadBufferData + textureSlicePitch * sliceIndex;
            const unsigned char* pSourceSlice = desc.pData + textureSlicePitch * sliceIndex;
            for (unsigned int rowIndex = 0; rowIndex < textureSubResourceFootprint.Footprint.Height; rowIndex++)
            {
                Memory::Copy(pSourceSlice + textureRowPitch * rowIndex, pDestinationSlice + textureSubResourceFootprint.Footprint.RowPitch * rowIndex, textureRowPitch);
            }
        }
        uploadBuffer->Unmap(0, nullptr);

        /*
        * Copy upload buffer content to texture
        */
        D3D12_TEXTURE_COPY_LOCATION destinationCopyLocation = {};
        destinationCopyLocation.pResource = pDXTexture->GetDXTexture();
        destinationCopyLocation.Type = D3D12_TEXTURE_COPY_TYPE_SUBRESOURCE_INDEX;
        destinationCopyLocation.PlacedFootprint = {};
        destinationCopyLocation.SubresourceIndex = 0;

        D3D12_TEXTURE_COPY_LOCATION sourceCopyLocation = {};
        sourceCopyLocation.pResource = uploadBuffer.Get();
        sourceCopyLocation.PlacedFootprint = textureSubResourceFootprint;
        sourceCopyLocation.Type = D3D12_TEXTURE_COPY_TYPE_PLACED_FOOTPRINT;
        sourceCopyLocation.SubresourceIndex = 0;

        mCmdList->CopyTextureRegion(&destinationCopyLocation, 0, 0, 0, &sourceCopyLocation, nullptr);

        /*
        * Set resource barrier
        */
        D3D12_RESOURCE_BARRIER barrier = {};
        barrier.Transition.pResource = pDXTexture->GetDXTexture();
        barrier.Transition.StateBefore = pDXTexture->GetDXResourceState();
        barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_GENERIC_READ;
        barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
        barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
        barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;

        pDXTexture->MutateDXResourceState(D3D12_RESOURCE_STATE_GENERIC_READ);

        mCmdList->ResourceBarrier(1, &barrier);

        mIntermediateUploadBuffers.Add(uploadBuffer);
    }
    void DX12GraphicsCommandList::ClearCachedStateCore()
    {
        mIntermediateUploadBuffers.Clear();
    }
    void DX12GraphicsCommandList::FreeFormerFramebufferBarriers()
    {
        Framebuffer* pCurrentFramebuffer = GetBoundFramebuffer();

        /*
        * Validate if a framebuffer still attached
        * IF it's still attached then barrier
        */
        if (pCurrentFramebuffer != nullptr)
        {
            if (pCurrentFramebuffer->IsSwapchain())
            {
                const Swapchain* pSwapchain = GetOwnerDevice()->GetSwapchain();
                const DX12Framebuffer* pDXFramebuffer = (const DX12Framebuffer*)pCurrentFramebuffer;
                DX12Texture* pColorTarget = ((DX12Texture*)pDXFramebuffer->GetColorTargets()[pSwapchain->GetCurrentImageIndex()].pTexture);
                DX12Texture* pDepthStencilTarget = (DX12Texture*)pDXFramebuffer->GetDepthStencilTarget().pTexture;
                Array<D3D12_RESOURCE_BARRIER> barriers;

                // Barrier color
                D3D12_RESOURCE_BARRIER colorTargetBarrier = {};
                colorTargetBarrier.Transition.pResource = pColorTarget->GetDXTexture();
                colorTargetBarrier.Transition.StateBefore = pColorTarget->GetDXResourceState();
                colorTargetBarrier.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;
                colorTargetBarrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
                colorTargetBarrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
                colorTargetBarrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
                barriers.Add(colorTargetBarrier);

                // Barrier depth stencil
                if (pDepthStencilTarget != nullptr)
                {
                    D3D12_RESOURCE_BARRIER depthStencilBarrier = {};
                    depthStencilBarrier.Transition.pResource = pDepthStencilTarget->GetDXTexture();
                    depthStencilBarrier.Transition.StateBefore = pDepthStencilTarget->GetDXResourceState();
                    depthStencilBarrier.Transition.StateAfter = D3D12_RESOURCE_STATE_DEPTH_READ;
                    depthStencilBarrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
                    depthStencilBarrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
                    depthStencilBarrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;

                    barriers.Add(depthStencilBarrier);

                    pDepthStencilTarget->MutateDXResourceState(D3D12_RESOURCE_STATE_DEPTH_READ);
                }

                mCmdList->ResourceBarrier(barriers.GetCursor(), barriers.GetData());

                pColorTarget->MutateDXResourceState(D3D12_RESOURCE_STATE_PRESENT);
            }
            else
            {
                const DX12Framebuffer* const pDXFramebuffer = (const DX12Framebuffer* const)pCurrentFramebuffer;
                const Array<FramebufferAttachmentDesc> colorAttachments = pDXFramebuffer->GetColorTargets();

                Array<D3D12_RESOURCE_BARRIER> barriers;

                //Barrier colors
                for (unsigned int i = 0; i < colorAttachments.GetCursor(); i++)
                {
                    DX12Texture* pColorTarget = (DX12Texture*)colorAttachments[i].pTexture;
                    D3D12_RESOURCE_BARRIER barrier = {};
                    barrier.Transition.pResource = pColorTarget->GetDXTexture();
                    barrier.Transition.StateBefore = pColorTarget->GetDXResourceState();
                    barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_COPY_DEST;
                    barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
                    barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
                    barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;

                    barriers.Add(barrier);

                    pColorTarget->MutateDXResourceState(D3D12_RESOURCE_STATE_COPY_DEST);
                }

                //Barrier depth stencil
                DX12Texture* const pDepthStencilTarget = (DX12Texture*)pDXFramebuffer->GetDepthStencilTarget().pTexture;
                if (pDepthStencilTarget != nullptr)
                {
                    D3D12_RESOURCE_BARRIER barrier = {};
                    barrier.Transition.pResource = pDepthStencilTarget->GetDXTexture();
                    barrier.Transition.StateBefore = pDepthStencilTarget->GetDXResourceState();
                    barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_DEPTH_READ;
                    barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
                    barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
                    barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;

                    barriers.Add(barrier);

                    pDepthStencilTarget->MutateDXResourceState(D3D12_RESOURCE_STATE_DEPTH_READ);
                }
                mCmdList->ResourceBarrier(barriers.GetCursor(), barriers.GetData());
            }
        }
    }
    void DX12GraphicsCommandList::OnDestroy()
    {
        mCmdList.Reset();
        mAllocator = nullptr;
    }
}