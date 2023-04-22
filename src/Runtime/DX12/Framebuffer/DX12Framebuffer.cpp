#include "DX12Framebuffer.h"
#include <Runtime/DX12/DX12Device.h>
#include <Runtime/DX12/Texture/DX12Texture.h>
#include <Runtime/DXGI/DXGIUtils.h>
#include <d3d12.h>
#include <Runtime/Assert/Assert.h>

namespace Portakal
{
    DX12Framebuffer::DX12Framebuffer(const FramebufferCreateDesc& desc, DX12Device* pDevice) : Framebuffer(desc,false)
    {
        ID3D12Device* pDXDevice = (ID3D12Device*)pDevice->GetDXDevice();

        /*
        * Create color heap
        */
        D3D12_DESCRIPTOR_HEAP_DESC colorDescriptorDesc = {};
        colorDescriptorDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
        colorDescriptorDesc.NumDescriptors = desc.ColorTargets.GetCursor();
        colorDescriptorDesc.NodeMask = 0;
        colorDescriptorDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;

        ASSERT(SUCCEEDED(pDXDevice->CreateDescriptorHeap(&colorDescriptorDesc, IID_PPV_ARGS(mColorHeap.GetAddressOf()))), "DX12Framebuffer", "Failed to create color attachments descriptor heap");

        /*
        * Create color render target
        */
        D3D12_CPU_DESCRIPTOR_HANDLE colorCpuHandle = mColorHeap->GetCPUDescriptorHandleForHeapStart();
        const unsigned int rtvIncrementSize = pDXDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

        for (unsigned int i = 0; i < desc.ColorTargets.GetCursor(); i++)
        {
            const FramebufferAttachmentDesc& attachmentDesc = desc.ColorTargets[i];

            DX12Texture* pTexture = (DX12Texture*)attachmentDesc.pTexture;

            D3D12_RENDER_TARGET_VIEW_DESC rtvDesc = {};
            rtvDesc.Format = DXGIUtils::GetTextureFormat(pTexture->GetTextureFormat());
            rtvDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;
            rtvDesc.Texture2D.MipSlice = attachmentDesc.MipLevel;
            rtvDesc.Texture2D.PlaneSlice = attachmentDesc.ArrayLayer;
            pDXDevice->CreateRenderTargetView(pTexture->GetDXTexture(), &rtvDesc, colorCpuHandle);

            colorCpuHandle.ptr += rtvIncrementSize;
        }

        /*
        * Create depth stencil
        */
        if (desc.DepthStencilTarget.pTexture != nullptr)
        {
            DX12Texture* pTexture = (DX12Texture*)desc.DepthStencilTarget.pTexture;

            D3D12_DESCRIPTOR_HEAP_DESC depthStencilDescriptorHeapDesc = {};
            depthStencilDescriptorHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
            depthStencilDescriptorHeapDesc.NumDescriptors = 1;
            depthStencilDescriptorHeapDesc.NodeMask = 0;
            depthStencilDescriptorHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;

            ASSERT(SUCCEEDED(pDXDevice->CreateDescriptorHeap(&depthStencilDescriptorHeapDesc, IID_PPV_ARGS(&mDepthStencilHeap))), "DX12Framebuffer", "Failed to create depth stencil descriptor heap");

            D3D12_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc = {};
            depthStencilViewDesc.Format = DXGIUtils::GetTextureFormat(pTexture->GetTextureFormat());
            depthStencilViewDesc.Flags = D3D12_DSV_FLAG_NONE;
            depthStencilViewDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
            depthStencilViewDesc.Texture2D.MipSlice = 1;

            pDXDevice->CreateDepthStencilView(pTexture->GetDXTexture(), nullptr, mDepthStencilHeap->GetCPUDescriptorHandleForHeapStart());
        }
    }
    DX12Framebuffer::DX12Framebuffer(const FramebufferCreateDesc& desc, const DXPTR<ID3D12DescriptorHeap> colorHeap, const DXPTR<ID3D12DescriptorHeap> depthStencilHeap) : Framebuffer(desc,true)
    {
        mColorHeap = colorHeap;
        mDepthStencilHeap = depthStencilHeap;
    }
    DX12Framebuffer::~DX12Framebuffer()
    {

    }
    void DX12Framebuffer::OnDestroy()
    {
        Framebuffer::OnDestroy();

        mColorHeap.Reset();
        mDepthStencilHeap.Reset();
    }
}