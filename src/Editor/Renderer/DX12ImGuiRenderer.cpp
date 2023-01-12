#include "DX12ImGuiRenderer.h"
#include <Runtime/DX12/DX12SwapchainFramebuffer.h>
#include <Libs/ImGui/backends/imgui_impl_dx12.h>
#include <Runtime/DXGI/DXGIUtils.h>
#include <Runtime/DX12/DX12CommandBuffer.h>
#include <Libs/ImGui/backends/imgui_impl_win32.h>
#include <Runtime/Win32/Win32Window.h>
#include <Runtime/DX12/DX12Device.h>
#include <Runtime/Assert/Assert.h>


namespace Portakal
{
    DX12ImGuiRenderer::DX12ImGuiRenderer(GraphicsDevice* pDevice) : ImGuiRenderer(pDevice)
    {
		const DX12SwapchainFramebuffer* pFramebuffer = (const DX12SwapchainFramebuffer*)pDevice->GetSwapchainFramebuffer();

		ID3D12Device* pDXDevice = ((DX12Device*)pDevice)->GetDXDevice();

		/*
		* Create descriptor heap for the font
		*/
		D3D12_DESCRIPTOR_HEAP_DESC desc = {};
		desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
		desc.NumDescriptors = 4;
		desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;

		ASSERT(SUCCEEDED(pDXDevice->CreateDescriptorHeap(&desc, IID_PPV_ARGS(&_fontHeap))), "ImGuiAPI-D3D12", "Failed to create the font descriptor heap"); //global imgui dx12 font heap

		/*
		* Init win32
		*/
		ImGui_ImplWin32_Init(((Win32Window*)pDevice->GetOwnerWindow())->GetWin32WindowHandle());

		/*
		* Init imgui d3d12
		*/
		ImGui_ImplDX12_Init(pDXDevice,
			pFramebuffer->GetBufferCount(),
			DXGIUtils::GetTextureFormat(pFramebuffer->GetSwapchainColorFormat()),
			_fontHeap.Get(),
			_fontHeap->GetCPUDescriptorHandleForHeapStart(),
			_fontHeap->GetGPUDescriptorHandleForHeapStart());

		_fontHeap->SetName(L"ImGui Font Heap");
    }
    DX12ImGuiRenderer::~DX12ImGuiRenderer()
    {
		ImGui_ImplDX12_Shutdown();
		ImGui_ImplWin32_Shutdown();
    }
    void DX12ImGuiRenderer::StartRenderingCore()
    {
		ImGui_ImplDX12_NewFrame();
    }
    void DX12ImGuiRenderer::FinalizeRenderingCore(CommandBuffer* pCmdBuffer)
    {
		ID3D12GraphicsCommandList* pList = (ID3D12GraphicsCommandList*)((DX12CommandBuffer*)pCmdBuffer)->GetDXCmdList();
		DX12SwapchainFramebuffer* pFramebuffer = (DX12SwapchainFramebuffer*)pCmdBuffer->GetOwnerDevice()->GetSwapchainFramebuffer();


		pCmdBuffer->BindFramebuffer(pFramebuffer);

		pCmdBuffer->ClearColor(0, 0.5f, 0.3f, 1.0f);

		ImGui_ImplDX12_RenderDrawData(ImGui::GetDrawData(), (ID3D12GraphicsCommandList*)pList);
    }
}