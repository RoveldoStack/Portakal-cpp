#include "DX11Framebuffer.h"

namespace Portakal
{
    DX11Framebuffer::DX11Framebuffer(const FramebufferCreateDesc& desc,DX11Device* pDevice) : Framebuffer(desc,false)
    {

    }
    DX11Framebuffer::DX11Framebuffer(const FramebufferCreateDesc& desc,const Array<ID3D11RenderTargetView*>& rtvs) : Framebuffer(desc, true)
    {
        mRtvs = rtvs;
    }
    DX11Framebuffer::~DX11Framebuffer()
    {
    }
    void DX11Framebuffer::SetDXRenderTargetViews(const Array<ID3D11RenderTargetView*>& rtvs)
    {
        mRtvs = rtvs;
    }
    void DX11Framebuffer::OnDestroy()
    {
    }
}