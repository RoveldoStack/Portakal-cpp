#include "DX11CommandList.h"
#include <Runtime/DX11/DX11Device.h>
#include <Runtime/Memory/Memory.h>
#include <Runtime/Graphics/Texture/TextureUtils.h>
#include <Runtime/DX11/Swapchain/DX11Swapchain.h>
#include <Runtime/Graphics/Framebuffer/Framebuffer.h>
#include <Runtime/DX11/Pipeline/DX11GraphicsPipeline.h>
#include <Runtime/Log/Log.h>
#include <Runtime/Assert/Assert.h>
#include <Runtime/Platform/PlatformError.h>
#include <Runtime/DX11/DX11DeviceObjects.h>
#include <d3d11shader.h>

namespace Portakal
{
    DX11CommandList::DX11CommandList(const CommandListCreateDesc& desc, DX11Device* pDevice) : mMapped(false), CommandList(desc,CommandQueueType::Graphics)
    {
        mDevice = pDevice->GetDXDevice();
        mContext = pDevice->GetDXImmediateContext();
        //ASSERT(SUCCEEDED(pDevice->GetDXDevice()->CreateDeferredContext(0, mContext.GetAddressOf())),"DX11CommandList","Failed to create a deferred context");
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
        pDevice->LockImmediateContext();
    }
    void DX11CommandList::UnlockCore()
    {
        DX11Device* pDevice = (DX11Device*)GetOwnerDevice();
        pDevice->UnlockImmediateContext();
        //ASSERT(SUCCEEDED(mContext->FinishCommandList(FALSE, mCmdList.GetAddressOf())), "DX11CommandList", "Failed to finish cmdlist");
    }
    void DX11CommandList::BindPipelineCore(Pipeline* pPipeline)
    {
        DX11GraphicsPipeline* pDXPipeline = (DX11GraphicsPipeline*)pPipeline;

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
        float factor[4] = {0,0,0,0};
        mContext->OMSetBlendState(pDXPipeline->GetDXBlendState(), factor, 0xffffffff);

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
            rect.bottom = desc.Bottom;
            rect.left = desc.Left;
            rect.top = desc.Top;
            rect.right = desc.Right;

            dx11Scissors.Add(rect);
        }

        mContext->RSSetScissorRects(dx11Scissors.GetCursor(), dx11Scissors.GetData());
    }
    void DX11CommandList::ClearColorCore(const unsigned int index, const Color4& color)
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
        const DX11Buffer* pDXBuffer = (const DX11Buffer*)pBuffer;
        ID3D11Buffer* pNativeBuffer = pDXBuffer->GetDXBuffer();

        unsigned int strides = pBuffer->GetSubItemSize();
        unsigned int offsets = 0;

        mContext->IASetVertexBuffers(0,1,&pNativeBuffer,&strides,&offsets);
    }
    void DX11CommandList::SetIndexBufferCore(GraphicsBuffer* pBuffer)
    {
        const DX11Buffer* pDXBuffer = (const DX11Buffer*)pBuffer;
         
        mContext->IASetIndexBuffer(pDXBuffer->GetDXBuffer(), pBuffer->GetSubItemSize() == sizeof(unsigned int) ? DXGI_FORMAT_R32_UINT : DXGI_FORMAT_R16_UINT, 0);
    }
    void DX11CommandList::CommitResourceTableCore(const unsigned int stageIndex,const unsigned int slotIndex,const ResourceTable* pTable)
    {
        const DX11ResourceTable* pDXTable = (const DX11ResourceTable*)pTable;

        const Array<ID3D11ShaderResourceView*>& resourceViews = pDXTable->GetDXResourceViews();
        const Array<ID3D11Buffer*>& buffers = pDXTable->GetDXBuffers();
        const Array<ID3D11SamplerState*>& samplers = pDXTable->GetDXSamplers();

        ID3D11ShaderResourceView** ppResourceViews = resourceViews.GetData();
        ID3D11Buffer** ppBuffers = buffers.GetData();
        ID3D11SamplerState** ppSamplers = samplers.GetData();

        const ResourceStateDesc resourceStateDesc = GetBoundPipeline()->GetResourceState();
        const ShaderStage stage = resourceStateDesc.Stages[stageIndex].Stage;

        const PipelineResourceTableDesc& tableDesc = resourceStateDesc.Stages[stageIndex].Tables[slotIndex];

        const unsigned int resourceViewCount = resourceViews.GetCursor();
        const unsigned int bufferCount = buffers.GetCursor();
        const unsigned int samplerCount = samplers.GetCursor();
        const unsigned int resourceViewOffset = tableDesc.TextureOffset;
        const unsigned int bufferOffset = tableDesc.BufferOffset;
        const unsigned int samplerOffset = tableDesc.SamplerOffset;

        /*
        * Set srvs
        */
        if (resourceViewCount > 0)
        {
            switch (stage)
            {
                case Portakal::ShaderStage::None:
                    break;
                case Portakal::ShaderStage::Vertex:
                {
                    mContext->VSSetShaderResources(resourceViewOffset, resourceViewCount, ppResourceViews);
                    break;
                }
                case Portakal::ShaderStage::Fragment:
                {
                    mContext->PSSetShaderResources(resourceViewOffset, resourceViewCount, ppResourceViews);
                    break;
                }
                case Portakal::ShaderStage::TesellationEval:
                {
                    mContext->DSSetShaderResources(resourceViewOffset, resourceViewCount, ppResourceViews);
                    break;
                }
                case Portakal::ShaderStage::TesellationControl:
                {
                    mContext->HSSetShaderResources(resourceViewOffset, resourceViewCount, ppResourceViews);
                    break;
                }
                case Portakal::ShaderStage::Compute:
                {
                    mContext->CSSetShaderResources(resourceViewOffset, resourceViewCount, ppResourceViews);
                    break;
                }
                default:
                    break;
            }
        }
       
        /*
        * Set constant buffers
        */
        if (bufferCount > 0)
        {
            switch (stage)
            {
            case Portakal::ShaderStage::None:
                break;
            case Portakal::ShaderStage::Vertex:
            {
                mContext->VSSetConstantBuffers(bufferOffset, bufferCount, ppBuffers);
                break;
            }
            case Portakal::ShaderStage::Fragment:
            {
                mContext->PSSetConstantBuffers(bufferOffset, bufferCount, ppBuffers);
                break;
            }
            case Portakal::ShaderStage::TesellationEval:
            {
                mContext->DSSetConstantBuffers(bufferOffset, bufferCount, ppBuffers);
                break;
            }
            case Portakal::ShaderStage::TesellationControl:
            {
                mContext->HSSetConstantBuffers(bufferOffset, bufferCount, ppBuffers);
                break;
            }
            case Portakal::ShaderStage::Compute:
            {
                mContext->CSSetConstantBuffers(bufferOffset, bufferCount, ppBuffers);
                break;
            }
            default:
                break;
            }
        }

        /*
        * Set samplers
        */
        if (samplerCount > 0)
        {
            switch (stage)
            {
            case Portakal::ShaderStage::None:
                break;
            case Portakal::ShaderStage::Vertex:
            {
                mContext->VSSetSamplers(samplerOffset, samplerCount, ppSamplers);
                break;
            }
            case Portakal::ShaderStage::Fragment:
            {
                mContext->PSSetSamplers(samplerOffset, samplerCount, ppSamplers);
                break;
            }
            case Portakal::ShaderStage::TesellationEval:
            {
                mContext->DSSetSamplers(samplerOffset, samplerCount, ppSamplers);
                break;
            }
            case Portakal::ShaderStage::TesellationControl:
            {
                mContext->HSSetSamplers(samplerOffset, samplerCount, ppSamplers);
                break;
            }
            case Portakal::ShaderStage::Compute:
            {
                mContext->CSSetSamplers(samplerOffset, samplerCount, ppSamplers);
                break;
            }
            default:
                break;
            }
        }

    }
    void DX11CommandList::DrawIndexedCore(const unsigned int indexCount, const unsigned int indexStartLocation, const unsigned int vertexStartLocation)
    {
        mContext->DrawIndexed(indexCount, indexStartLocation,vertexStartLocation);
    }
    void DX11CommandList::DispatchCore(const unsigned int sizeX, const unsigned int sizeY, const unsigned int sizeZ)
    {
        mContext->Dispatch(sizeX, sizeY, sizeZ);
    }
    void DX11CommandList::UpdateBufferCore(const GraphicsBufferUpdateDesc& desc, GraphicsBuffer* pBuffer)
    {
        DX11Buffer* pDX11Buffer = (DX11Buffer*)pBuffer;

        D3D11_MAPPED_SUBRESOURCE subResource = {};
        ASSERT(SUCCEEDED(mContext->Map(pDX11Buffer->GetDXBuffer(), 0,D3D11_MAP_WRITE_NO_OVERWRITE , 0, &subResource)), "DX11CommandList", "Failed to map buffer");

        Memory::Copy(desc.pData, (Byte*)subResource.pData + desc.Offset, desc.Size);

        mContext->Unmap(pDX11Buffer->GetDXBuffer(), 0);

       // mMapped = true;
    }
    void DX11CommandList::UpdateTextureCore(const TextureUpdateDesc& desc, Texture* pTexture)
    {

        DX11Texture* pTargetTexture = (DX11Texture*)pTexture;

        if (pTexture->GetTextureUsage() &  TextureUsage::CpuWrite)
        {
            D3D11_MAPPED_SUBRESOURCE subResource = {};

            if (FAILED(mContext->Map(pTargetTexture->GetDXTexture(), 0, D3D11_MAP_WRITE_DISCARD, 0, &subResource)))
            {
                LOG("DX11CommandList", "Failed to map");
                return;
            }

            const unsigned long long size = TextureUtils::GetFormatSize(pTexture->GetTextureFormat()) * pTexture->GetWidth() * pTexture->GetHeight();
            const unsigned long long expectedRowPitch = pTexture->GetWidth() * TextureUtils::GetFormatSize(pTexture->GetTextureFormat());

            if (size != expectedRowPitch)
            {
                Memory::Copy(desc.pData, subResource.pData, size);
            }
            else
            {
                const unsigned int height = pTargetTexture->GetHeight();
                for (unsigned int i = 0; i < height; i++)
                {
                    Memory::Copy((Byte*)desc.pData + i * expectedRowPitch, (Byte*)subResource.pData + i * subResource.RowPitch, subResource.RowPitch);
                }
            }


            mContext->Unmap(pTargetTexture->GetDXTexture(), 0);
        }
        else
        {
            const unsigned int pitch = TextureUtils::GetFormatSize(pTargetTexture->GetTextureFormat()) * pTargetTexture->GetWidth();
            mContext->UpdateSubresource(pTargetTexture->GetDXTexture(),0,nullptr,desc.pData,pitch, 0);
        }

       // mMapped = true;
    }
    void DX11CommandList::ClearCachedStateCore()
    {
        mMapped = false;
    }
  
}