#include "DX11CommandList.h"
#include <Runtime/DX11/DX11Device.h>
#include "DX11Texture.h"
#include <Runtime/Memory/Memory.h>
#include <Runtime/Graphics/TextureUtils.h>
#include <Runtime/DX11/DX11Swapchain.h>
#include <Runtime/Graphics/Framebuffer.h>
#include <Runtime/Log/Log.h>

namespace Portakal
{
    DX11CommandList::DX11CommandList(const CommandListCreateDesc& desc, DX11Device* pDevice) : CommandList(desc,CommandQueueType::Graphics)
    {
        mDevice = pDevice->GetDXDevice();
        mContext = pDevice->GetDXContext();
    }
    DX11CommandList::~DX11CommandList()
    {
    }
    void DX11CommandList::OnDestroy()
    {

    }
    void DX11CommandList::LockCore()
    {
        DX11Device* pDevice = (DX11Device*)GetOwnerDevice();
        pDevice->LockContext();
    }
    void DX11CommandList::UnlockCore()
    {
        DX11Device* pDevice = (DX11Device*)GetOwnerDevice();
        pDevice->UnlockContext();

    }
    void DX11CommandList::BindPipelineCore(Pipeline* pPipeline)
    {

    }
    void DX11CommandList::BindFramebufferCore(Framebuffer* pFramebuffer)
    {
        Array<ID3D11RenderTargetView*> pRtvs;
        DX11Swapchain* pSwapchain = (DX11Swapchain*)GetOwnerDevice()->GetSwapchain();
        pRtvs.Add(pSwapchain->GetDXCurrentRtv());
    

        mContext->OMSetRenderTargets(pRtvs.GetCursor(), pRtvs.GetData(), nullptr);

    }
    void DX11CommandList::SetViewportsCore(const Array<ViewportDesc>& viewports)
    {
        Array<D3D11_VIEWPORT> dx11Viewports;
        for (unsigned int i = 0; i < viewports.GetCursor(); i++)
        {
            const ViewportDesc& desc = viewports[i];

            D3D11_VIEWPORT viewport = {};
            viewport.Width = desc.Width;
            viewport.Height = desc.Height;
            viewport.TopLeftX = desc.X;
            viewport.TopLeftY = desc.Y;
            viewport.MinDepth = desc.MinDepth;
            viewport.MaxDepth = desc.MaxDepth;

            dx11Viewports.Add(viewport);
        }

        mContext->RSSetViewports(dx11Viewports.GetCursor(), dx11Viewports.GetData());
    }
    void DX11CommandList::SetScissorsCore(const Array<ScissorDesc>& scissors)
    {
        Array<D3D11_RECT> dx11Scissors;
        for (unsigned int i = 0; i < scissors.GetCursor(); i++)
        {
            const ScissorDesc& desc = scissors[i];

            D3D11_RECT rect = {};
            rect.bottom = desc.Height * desc.Y;
            rect.left = 0;
            rect.top = 0;
            rect.right = desc.Width - desc.X;

            dx11Scissors.Add(rect);
        }

        mContext->RSSetScissorRects(dx11Scissors.GetCursor(), dx11Scissors.GetData());
    }
    void DX11CommandList::ClearColorCore(const unsigned int index, const ColorRgba& color)
    {
        Framebuffer* pBoundFramebuffer = GetBoundFramebuffer();

        ID3D11RenderTargetView* pRtv = nullptr;
        if (pBoundFramebuffer->IsSwapchain())
        {
            DX11Swapchain* pSwapchain = (DX11Swapchain*)GetOwnerDevice()->GetSwapchain();
            pRtv = pSwapchain->GetDXCurrentRtv();
        }
        else
        {

        }

        if (pRtv == nullptr)
            return;

        const float clearColor[] = { color.R / 255.0f,color.G / 255.0f,color.B / 255.0f,color.A / 255.0f };
        mContext->ClearRenderTargetView(pRtv, clearColor);

    }
    void DX11CommandList::ClearColorCore(const unsigned int index, const ColorRgbaF& color)
    {
        Framebuffer* pBoundFramebuffer = GetBoundFramebuffer();

        ID3D11RenderTargetView* pRtv = nullptr;
        if (pBoundFramebuffer->IsSwapchain())
        {
            DX11Swapchain* pSwapchain = (DX11Swapchain*)GetOwnerDevice()->GetSwapchain();
            pRtv = pSwapchain->GetDXCurrentRtv();
        }
        else
        {

        }

        if (pRtv == nullptr)
            return;

        const float clearColor[] = { color.R / 255.0f,color.G / 255.0f,color.B / 255.0f,color.A / 255.0f };
        mContext->ClearRenderTargetView(pRtv, clearColor);
    }
    void DX11CommandList::ClearDepthCore(const float depth)
    {
       
    }
    void DX11CommandList::ClearStencilCore(const int stencil)
    {

    }
    void DX11CommandList::SetVertexBufferCore(GraphicsBuffer* pBuffer)
    {

    }
    void DX11CommandList::SetIndexBufferCore(GraphicsBuffer* pBuffer)
    {

    }
    void DX11CommandList::CommitResourceTableCore(const unsigned int slotIndex, const GraphicsResourceTable* pTable)
    {

    }
    void DX11CommandList::DrawIndexedCore(const unsigned int indexCount)
    {

    }
    void DX11CommandList::UpdateBufferCore(const GraphicsBufferUpdateDesc& desc, GraphicsBuffer* pBuffer)
    {

    }
    void DX11CommandList::UpdateTextureCore(const TextureUpdateDesc& desc, Texture* pTexture)
    {
        DX11Texture* pTargetTexture = (DX11Texture*)pTexture;


        D3D11_MAPPED_SUBRESOURCE subResource = {};

        mContext->Map(pTargetTexture->GetDXTexture(), 0, D3D11_MAP_WRITE_DISCARD, 0, &subResource);

        const unsigned long long size = TextureUtils::GetFormatSize(pTexture->GetTextureFormat())*pTexture->GetWidth()*pTexture->GetHeight();
        const unsigned long long expectedSize = subResource.RowPitch * pTexture->GetHeight();

        if (size != expectedSize)
        {
            LOG("Yo", "Yo");
        }
        Memory::Copy(desc.pData, subResource.pData,size);

        mContext->Unmap(pTargetTexture->GetDXTexture(), 0);
    }
    void DX11CommandList::ClearCachedStateCore()
    {

    }
}