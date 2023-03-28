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
            D3D11CreateDevice(mAdapter.Get(), D3D_DRIVER_TYPE_UNKNOWN, NULL, D3D11_CREATE_DEVICE_DEBUG, NULL, NULL, D3D11_SDK_VERSION, mDevice.GetAddressOf(), NULL, mContext.GetAddressOf());
#else
            D3D11CreateDevice(mAdapter.Get(), D3D_DRIVER_TYPE_UNKNOWN, NULL, NULL, NULL, NULL, D3D11_SDK_VERSION, mDevice.GetAddressOf(), NULL, mContext.GetAddressOf());
#endif

            bAdapterFound = true;
            adapterIndex++;
            break;
        }

        ASSERT(bAdapterFound, "DX11Device", "Failed to find any suitable device");

        mCriticalSection = PlatformCriticalSection::Create();
    }
    DX11Device::DX11Device()
    {
        mCriticalSection = PlatformCriticalSection::Create();
    }
    DX11Device::~DX11Device()
    {

    }
    Framebuffer* DX11Device::CreateSwapchainFramebuffer(const FramebufferCreateDesc& desc, const Array<ID3D11RenderTargetView*>& rtvs)
    {
        DX11Framebuffer* framebuffer = new DX11Framebuffer(desc, rtvs);

        RegisterChildObject(framebuffer);

        return framebuffer;
    }
    void DX11Device::LockContext()
    {
        mCriticalSection->Lock();
    }
    void DX11Device::UnlockContext()
    {
        mCriticalSection->Release();
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
        return nullptr;
    }
    Shader* DX11Device::CreateShaderCore(const ShaderCreateDesc& desc)
    {
        return nullptr;
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
        return nullptr;
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

    }
    void DX11Device::SubmitCommandsCore(const Array<CommandList*>& cmdBuffers)
    {

    }
}