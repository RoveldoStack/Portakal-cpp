#include "DX11CommandList.h"
#include <Runtime/DX11/DX11Device.h>
#include "DX11Texture.h"
#include <Runtime/Memory/Memory.h>
#include <Runtime/Graphics/TextureUtils.h>
#include <Runtime/DX11/DX11Swapchain.h>
#include <Runtime/Graphics/Framebuffer.h>
#include <Runtime/DX11/DX11Pipeline.h>
#include <Runtime/Log/Log.h>
#include <Runtime/Assert/Assert.h>
#include <Runtime/Platform/PlatformError.h>
#include "DX11Framebuffer.h"
#include "DX11Buffer.h"
#include "DX11ResourceTable.h"

namespace Portakal
{
    DX11CommandList::DX11CommandList(const CommandListCreateDesc& desc, DX11Device* pDevice) : CommandList(desc,CommandQueueType::Graphics)
    {
        mDevice = pDevice->GetDXDevice();
        pDevice->GetDXDevice()->CreateDeferredContext(0,mContext.GetAddressOf());
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
    }
    void DX11CommandList::UnlockCore()
    {
        DX11Device* pDevice = (DX11Device*)GetOwnerDevice();

        ASSERT(SUCCEEDED(mContext->FinishCommandList(FALSE, mCmdList.GetAddressOf())), "DX11CommandList", "Failed to finish cmdlist");
    }
    void DX11CommandList::BindPipelineCore(Pipeline* pPipeline)
    {
        DX11Pipeline* pDXPipeline = (DX11Pipeline*)pPipeline;

        /*
        * Set rasterizer
        */
        mContext->RSSetState(pDXPipeline->GetDXRasterizerState());

        /*
        * Set depth stencil state
        */
        mContext->OMSetDepthStencilState(pDXPipeline->GetDXDepthStencilState(),0);

        /*
        * Set blending state
        */
        mContext->OMSetBlendState(pDXPipeline->GetDXBlendState(), nullptr, 0);

        /*
        * Set input layout
        */
        mContext->IASetInputLayout(pDXPipeline->GetDXInputLayout());
        mContext->IASetPrimitiveTopology(pDXPipeline->GetDXTopology());

        /*
        * Set shader
        */
        {
            ID3D11VertexShader* pShader = pDXPipeline->GetDXVertexShader();
            if (pShader != nullptr)
            {
                mContext->VSSetShader(pShader, nullptr, 0);
            }
        }
        {
            ID3D11PixelShader* pShader = pDXPipeline->GetDXPixelShader();
            if (pShader != nullptr)
            {
                mContext->PSSetShader(pShader, nullptr, 0);
            }
        }
        {
            ID3D11DomainShader* pShader = pDXPipeline->GetDXDomainShader();
            if (pShader != nullptr)
            {
                mContext->DSSetShader(pShader, nullptr, 0);
            }
        }
        {
            ID3D11HullShader* pShader = pDXPipeline->GetDXHullShader();
            if (pShader != nullptr)
            {
                mContext->HSSetShader(pShader, nullptr, 0);
            }
        }
        {
            ID3D11ComputeShader* pShader = pDXPipeline->GetDXComputeShader();
            if (pShader != nullptr)
            {
                mContext->CSSetShader(pShader, nullptr, 0);
            }
        }

    }
    void DX11CommandList::BindFramebufferCore(Framebuffer* pFramebuffer)
    {
        DX11Framebuffer* pDX11Framebuffer = (DX11Framebuffer*)pFramebuffer;

        Array<ID3D11RenderTargetView*> rtvs = pDX11Framebuffer->GetDXRtvs();
        ID3D11DepthStencilView* pDsv = pDX11Framebuffer->GetDXDsv();

        mContext->OMSetRenderTargets(rtvs.GetCursor(), rtvs.GetData(), pDsv);
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

        /*
        * Get RTV
        */
        ID3D11RenderTargetView* pRtv = nullptr;
        if (pBoundFramebuffer->IsSwapchain())
        {
            DX11Framebuffer* pDXFramebuffer = (DX11Framebuffer*)pBoundFramebuffer;

            pRtv = pDXFramebuffer->GetDXRtvs()[0];
        }
        else
        {
            DX11Framebuffer* pDXFramebuffer = (DX11Framebuffer*)pBoundFramebuffer;

            pRtv = pDXFramebuffer->GetDXRtvs()[index];
        }

        if (pRtv == nullptr)
            return;


        const float clearColor[] = { color.R / 255.0f,color.G / 255.0f,color.B / 255.0f,color.A / 255.0f };
        mContext->ClearRenderTargetView(pRtv, clearColor);

    }
    void DX11CommandList::ClearColorCore(const unsigned int index, const ColorRgbaF& color)
    {
        Framebuffer* pBoundFramebuffer = GetBoundFramebuffer();

        /*
        * Get rtv
        */
        ID3D11RenderTargetView* pRtv = nullptr;
        if (pBoundFramebuffer->IsSwapchain())
        {
            DX11Framebuffer* pDXFramebuffer = (DX11Framebuffer*)pBoundFramebuffer;

            pRtv = pDXFramebuffer->GetDXRtvs()[0];
        }
        else
        {
            DX11Framebuffer* pDXFramebuffer = (DX11Framebuffer*)pBoundFramebuffer;

            pRtv = pDXFramebuffer->GetDXRtvs()[index];
        }

        if (pRtv == nullptr)
            return;

        mContext->ClearRenderTargetView(pRtv, &color.R);
    }
    void DX11CommandList::ClearDepthCore(const float depth)
    {
        const DX11Framebuffer* pBoundFramebuffer = (const DX11Framebuffer*)GetBoundFramebuffer();

        ID3D11DepthStencilView* pView = pBoundFramebuffer->GetDXDsv();
        if (pView == nullptr)
            return;
        mContext->ClearDepthStencilView(pView, D3D11_CLEAR_DEPTH, depth, 0);
    }
    void DX11CommandList::ClearStencilCore(const int stencil)
    {
        const DX11Framebuffer* pBoundFramebuffer = (const DX11Framebuffer*)GetBoundFramebuffer();

        ID3D11DepthStencilView* pView = pBoundFramebuffer->GetDXDsv();
        if (pView == nullptr)
            return;

        mContext->ClearDepthStencilView(pView, D3D11_CLEAR_STENCIL, 0, stencil);
    }
    void DX11CommandList::SetVertexBufferCore(GraphicsBuffer* pBuffer)
    {
        UINT stride = 0;
        UINT offsets = 0;
        mContext->IASetVertexBuffers(0,1,nullptr,&stride,&offsets);
    }
    void DX11CommandList::SetIndexBufferCore(GraphicsBuffer* pBuffer)
    {
        mContext->IASetIndexBuffer(nullptr, DXGI_FORMAT_UNKNOWN, 0);
    }
    void DX11CommandList::CommitResourceTableCore(const unsigned int slotIndex, const ResourceTable* pTable)
    {
        const DX11ResourceTable* pDXTable = (const DX11ResourceTable*)pTable;
        const Array<ID3D11ShaderResourceView*>& srvs = pDXTable->GetDXSrvs();
        const Array<ID3D11Buffer*>& buffers = pDXTable->GetDXBuffers();
        const Array<ID3D11SamplerState*>& samplers = pDXTable->GetDXSamplers();

        ShaderStage stage = GetBoundPipeline()->GetResourceState().Slots[slotIndex].Stage;

        /*
        * Set srvs
        */
        switch (stage)
        {
            case Portakal::ShaderStage::None:
                break;
            case Portakal::ShaderStage::Vertex:
            {
                mContext->VSSetShaderResources(0,srvs.GetCursor(),srvs.GetData());
                break;
            }
            case Portakal::ShaderStage::Fragment:
            {
                mContext->PSSetShaderResources(0, srvs.GetCursor(), srvs.GetData());
                break;
            }
            case Portakal::ShaderStage::TesellationEval:
            {
                mContext->DSSetShaderResources(0, srvs.GetCursor(), srvs.GetData());
                break;
            }
            case Portakal::ShaderStage::TesellationControl:
            {
                mContext->HSSetShaderResources(0, srvs.GetCursor(), srvs.GetData());
                break;
            }
            case Portakal::ShaderStage::Compute:
            {
                mContext->CSSetShaderResources(0, srvs.GetCursor(), srvs.GetData());
                break;
            }
            default:
                break;
        }

        /*
        * Set constant buffers
        */
        switch (stage)
        {
        case Portakal::ShaderStage::None:
            break;
        case Portakal::ShaderStage::Vertex:
        {
            mContext->VSSetConstantBuffers(0, buffers.GetCursor(), buffers.GetData());
            break;
        }
        case Portakal::ShaderStage::Fragment:
        {
            mContext->PSSetConstantBuffers(0, buffers.GetCursor(), buffers.GetData());
            break;
        }
        case Portakal::ShaderStage::TesellationEval:
        {
            mContext->DSSetConstantBuffers(0, buffers.GetCursor(), buffers.GetData());
            break;
        }
        case Portakal::ShaderStage::TesellationControl:
        {
            mContext->HSSetConstantBuffers(0, buffers.GetCursor(), buffers.GetData());
            break;
        }
        case Portakal::ShaderStage::Compute:
        {
            mContext->CSSetConstantBuffers(0, buffers.GetCursor(), buffers.GetData());
            break;
        }
        default:
            break;
        }

        /*
        * Set samplers
        */
        switch (stage)
        {
        case Portakal::ShaderStage::None:
            break;
        case Portakal::ShaderStage::Vertex:
        {
            mContext->VSSetSamplers(0, samplers.GetCursor(), samplers.GetData());
            break;
        }
        case Portakal::ShaderStage::Fragment:
        {
            mContext->PSSetSamplers(0, samplers.GetCursor(), samplers.GetData());
            break;
        }
        case Portakal::ShaderStage::TesellationEval:
        {
            mContext->DSSetSamplers(0, samplers.GetCursor(), samplers.GetData());
            break;
        }
        case Portakal::ShaderStage::TesellationControl:
        {
            mContext->HSSetSamplers(0, samplers.GetCursor(), samplers.GetData());
            break;
        }
        case Portakal::ShaderStage::Compute:
        {
            mContext->CSSetSamplers(0, samplers.GetCursor(), samplers.GetData());
            break;
        }
        default:
            break;
        }

    }
    void DX11CommandList::DrawIndexedCore(const unsigned int indexCount)
    {
        mContext->DrawIndexed(indexCount, 0, 0);
    }
    void DX11CommandList::DispatchCore(const unsigned int sizeX, const unsigned int sizeY, const unsigned int sizeZ)
    {
        mContext->Dispatch(sizeX, sizeY, sizeZ);
    }
    void DX11CommandList::UpdateBufferCore(const GraphicsBufferUpdateDesc& desc, GraphicsBuffer* pBuffer)
    {
        DX11Buffer* pDX11Buffer = (DX11Buffer*)pBuffer;

        D3D11_MAPPED_SUBRESOURCE subResource = {};

        mContext->Map(pDX11Buffer->GetDXBuffer(), 0, D3D11_MAP_WRITE_DISCARD, 0, &subResource);
        Memory::Copy((desc.pData+desc.Offset), subResource.pData, desc.Size);
        mContext->Unmap(pDX11Buffer->GetDXBuffer(), 0);
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
            LOG("DX11CommandList", "Unexpected rowpitch for texture update");
        }

        Memory::Copy(desc.pData, subResource.pData,size);

        mContext->Unmap(pTargetTexture->GetDXTexture(), 0);
    }
    void DX11CommandList::ClearCachedStateCore()
    {

    }
  
}