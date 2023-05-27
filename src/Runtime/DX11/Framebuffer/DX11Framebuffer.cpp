#include "DX11Framebuffer.h"
#include <Runtime/DX11/DX11Device.h>
#include <Runtime/DXGI/DXGIUtils.h>
#include <Runtime/DX11/Texture/DX11Texture.h>
#include <Runtime/Assert/Assert.h>

namespace Portakal
{
   

    DX11Framebuffer::DX11Framebuffer(const FramebufferCreateDesc& desc,const bool bSwapchain,DX11Device* pDevice) : Framebuffer(desc, bSwapchain)
    {
        /*
        * Create rtvs
        */
        for (unsigned int i = 0; i < desc.ColorTargets.GetCursor(); i++)
        {
            const FramebufferAttachmentDesc& attachment = desc.ColorTargets[i];
            DX11Texture* pTexture = (DX11Texture*)attachment.pTexture;

            D3D11_RENDER_TARGET_VIEW_DESC rtvDesc = {};
            rtvDesc.Buffer = {};
            rtvDesc.Format = DXGIUtils::GetTextureFormat(attachment.pTexture->GetTextureFormat());
            rtvDesc.Texture2D.MipSlice = attachment.MipLevel;
            rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;

            DXPTR<ID3D11RenderTargetView> rtv;
            ASSERT(SUCCEEDED(pDevice->GetDXDevice()->CreateRenderTargetView(pTexture->GetDXTexture(), &rtvDesc, rtv.GetAddressOf())),"DX11Framebuffer","Failed to create rtv");
            mRtvs.Add(rtv);
        }

        /*
        * Create dsv
        */
        if (desc.DepthStencilTarget.pTexture != nullptr)
        {
            DX11Texture* pTexture = (DX11Texture*)desc.DepthStencilTarget.pTexture;
            D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc = {};
            dsvDesc.Format = DXGIUtils::GetTextureFormat(pTexture->GetTextureFormat());
            dsvDesc.Texture2D.MipSlice = 0;
            dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;


           ASSERT(SUCCEEDED(pDevice->GetDXDevice()->CreateDepthStencilView(pTexture->GetDXTexture(), &dsvDesc, mDsv.GetAddressOf())),"DX11Framebuffer","Failed to create dsv");
        }
    }
   
    DX11Framebuffer::~DX11Framebuffer()
    {

    }

    void DX11Framebuffer::ResizeDXSwapchainFramebuffer(const FramebufferCreateDesc& desc)
    {
        /*
        * First delete resources
        */
        DeleteDXResources();

        DX11Device* pDevice = (DX11Device*)GetOwnerDevice();

        /*
        * Create rtvs
        */
        for (unsigned int i = 0; i < desc.ColorTargets.GetCursor(); i++)
        {
            const FramebufferAttachmentDesc& attachment = desc.ColorTargets[i];
            DX11Texture* pTexture = (DX11Texture*)attachment.pTexture;

            D3D11_RENDER_TARGET_VIEW_DESC rtvDesc = {};
            rtvDesc.Buffer = {};
            rtvDesc.Format = DXGIUtils::GetTextureFormat(attachment.pTexture->GetTextureFormat());
            rtvDesc.Texture2D.MipSlice = attachment.MipLevel;
            rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;

            DXPTR<ID3D11RenderTargetView> rtv;
            ASSERT(SUCCEEDED(pDevice->GetDXDevice()->CreateRenderTargetView(pTexture->GetDXTexture(), &rtvDesc, rtv.GetAddressOf())), "DX11Framebuffer", "Failed to create rtv");
            mRtvs.Add(rtv);
        }

        /*
        * Create dsv
        */
        if (desc.DepthStencilTarget.pTexture != nullptr)
        {
            DX11Texture* pTexture = (DX11Texture*)desc.DepthStencilTarget.pTexture;
            D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc = {};
            dsvDesc.Format = DXGIUtils::GetTextureFormat(pTexture->GetTextureFormat());
            dsvDesc.Texture2D.MipSlice = 0;
            dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;


            ASSERT(SUCCEEDED(pDevice->GetDXDevice()->CreateDepthStencilView(pTexture->GetDXTexture(), &dsvDesc, mDsv.GetAddressOf())), "DX11Framebuffer", "Failed to create dsv");
        }

        /*
        * Set attachments
        */
        SetColorTargets(desc.ColorTargets);
        SetDepthStencilTarget(desc.DepthStencilTarget);
    }

    Array<ID3D11RenderTargetView*> DX11Framebuffer::GetDXRtvs() const noexcept
    {
        Array<ID3D11RenderTargetView*> rtvs;
        for (unsigned int i = 0; i < mRtvs.GetCursor(); i++)
        {
            rtvs.Add(mRtvs[i].Get());
        }

        return rtvs;
    }
   
    void DX11Framebuffer::OnDestroy()
    {
        DeleteDXResources();

        Framebuffer::OnDestroy();
    }
    void DX11Framebuffer::DeleteDXResources()
    {
        mRtvs.Clear();
        mDsv.Reset();
    }
}