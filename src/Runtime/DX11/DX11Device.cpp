#include "DX11Device.h"
#include <Runtime/DX11/DX11DeviceObjects.h>
#include <Runtime/Win32/Win32Window.h>
#include <Runtime/Assert/Assert.h>
#include <Runtime/Graphics/WindowedGraphicsDeviceCreateDesc.h>

namespace Portakal
{
    DX11Device::DX11Device(const WindowedGraphicsDeviceCreateDesc& desc) : GraphicsDevice(desc.pOwnerWindow)
    {

        Win32Window* pWin32Window = (Win32Window*)desc.pOwnerWindow;

        ASSERT(SUCCEEDED(CreateDXGIFactory2(0, IID_PPV_ARGS(&mFactory))), "DX11Device", "Failed to create dxgi factory");

        int adapterIndex = 0;
        bool bAdapterFound = false;

        while (mFactory->EnumAdapters1(adapterIndex, mAdapter.GetAddressOf()) != DXGI_ERROR_NOT_FOUND)
        {
            DXGI_ADAPTER_DESC1 adapterDesc = {};
            mAdapter->GetDesc1(&adapterDesc);

            if (adapterDesc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE)
            {
                adapterIndex++;
                continue;
            }

#if PORTAKAL_DEBUG
            D3D11CreateDevice(mAdapter.Get(), D3D_DRIVER_TYPE_UNKNOWN, NULL, D3D11_CREATE_DEVICE_DEBUG, NULL, NULL, D3D11_SDK_VERSION, mDevice.GetAddressOf(), NULL, mImmediateContext.GetAddressOf());
#else
            D3D11CreateDevice(mAdapter.Get(), D3D_DRIVER_TYPE_UNKNOWN, NULL, NULL, NULL, NULL, D3D11_SDK_VERSION, mDevice.GetAddressOf(), NULL, mImmediateContext.GetAddressOf());
#endif

            SetMemory(adapterDesc.DedicatedVideoMemory);

            bAdapterFound = true;
            adapterIndex++;
            break;
        }

        ASSERT(bAdapterFound, "DX11Device", "Failed to find any suitable device");

        mContextBarrier = PlatformCriticalSection::Create();
    }
    DX11Device::DX11Device()
    {
        mContextBarrier = PlatformCriticalSection::Create();
    }
    DX11Device::~DX11Device()
    {

    }
    Texture* DX11Device::CreateSwapchainTexture(const TextureCreateDesc& desc, const DXPTR<ID3D11Resource>& texture)
    {
        Texture* pTexture = new DX11Texture(desc, texture, this);

        RegisterChildObject(pTexture);

        return pTexture;
    }
    Framebuffer* DX11Device::CreateSwapchainFramebuffer(const FramebufferCreateDesc& desc)
    {
        Framebuffer* pFramebuffer = new DX11Framebuffer(desc, true, this);

        RegisterChildObject(pFramebuffer);

        return pFramebuffer;
    }
    void DX11Device::LockImmediateContext()
    {
        mContextBarrier->Lock();
    }
    void DX11Device::UnlockImmediateContext()
    {
        mContextBarrier->Release();
    }
    void DX11Device::SwapbuffersCore()
    {
        GetSwapchain()->Swapbuffers();
    }
    CommandList* DX11Device::CreateGraphicsCommandListCore(const CommandListCreateDesc& desc)
    {
        return new DX11CommandList(desc, this);
    }
    GraphicsBuffer* DX11Device::CreateBufferCore(const GraphicsBufferCreateDesc& desc)
    {
        return new DX11Buffer(desc,this);
    }
    Shader* DX11Device::CreateShaderCore(const ShaderCreateDesc& desc)
    {
        return new DX11Shader(desc,this);
    }
    Texture* DX11Device::CreateTextureCore(const TextureCreateDesc& desc)
    {
        return new DX11Texture(desc,this);
    }
    Sampler* DX11Device::CreateSamplerCore(const SamplerCreateDesc& desc)
    {
        return nullptr;
    }
    Framebuffer* DX11Device::CreateFramebufferCore(const FramebufferCreateDesc& desc)
    {
        return new DX11Framebuffer(desc,false,this);
    }
    Swapchain* DX11Device::CreateSwapchainCore(const SwapchainCreateDesc& desc)
    {
        return new DX11Swapchain(desc,this);
    }
    Pipeline* DX11Device::CreateGraphicsPipelineCore(const GraphicsPipelineCreateDesc& desc)
    {
        return nullptr;
    }
    Pipeline* DX11Device::CreateComputePipelineCore(const ComputePipelineCreateDesc& desc)
    {
        return nullptr;
    }
    ResourceTable* DX11Device::CreateResourceTableCore(const ResourceTableCreateDesc& desc)
    {
        return new DX11ResourceTable(desc,this);
    }
    Fence* DX11Device::CreateFenceCore()
    {
        return nullptr;
    }
    void DX11Device::UpdateBufferCore(GraphicsBuffer* pBuffer, const GraphicsBufferUpdateDesc& desc)
    {

    }
    void DX11Device::WaitForFinishCore()
    {
        mContextBarrier->Lock();

        DXPTR<ID3D11Query> query = 0;
        D3D11_QUERY_DESC desc = { D3D11_QUERY_EVENT,0 };
        mDevice->CreateQuery(&desc, query.GetAddressOf());

        mImmediateContext->Flush();
        mImmediateContext->End(query.Get());

        while (mImmediateContext->GetData(query.Get(), nullptr, 0, 0) == S_FALSE)
        {

        }

        mContextBarrier->Release();
    }
    void DX11Device::SubmitCommandsCore(const Array<CommandList*>& cmdBuffers)
    {
        mContextBarrier->Lock();
        for (unsigned int i = 0; i < cmdBuffers.GetCursor(); i++)
        {
            DX11CommandList* pCmdList = (DX11CommandList*)cmdBuffers[i];

            mImmediateContext->ExecuteCommandList(pCmdList->GetDXCmdList(), FALSE);
        }
        mContextBarrier->Release();
    }
}