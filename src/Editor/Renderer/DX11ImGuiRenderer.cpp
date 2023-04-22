#include "DX11ImGuiRenderer.h"
#include <Runtime/Win32/Win32Window.h>
#include <Runtime/DX11/DX11Device.h>
#include <Editor/Renderer/DX11ImGuiTextureBinding.h>
#include <Libs/ImGui/backends/imgui_impl_dx11.h>
#include <Libs/ImGui/backends/imgui_impl_win32.h>
#include <Runtime/Graphics/Command/CommandList.h>
#include <Runtime/Graphics/Swapchain/Swapchain.h>
#include <Runtime/DX11/Swapchain/DX11Swapchain.h>
#include <Runtime/DX11/Framebuffer/DX11Framebuffer.h>

namespace Portakal
{
    DX11ImGuiRenderer::DX11ImGuiRenderer(GraphicsDevice* pDevice) : ImGuiRenderer(pDevice)
    {
        DX11Device* pDX11Device = (DX11Device*)pDevice;

        ImGui_ImplWin32_Init(((Win32Window*)pDevice->GetOwnerWindow())->GetWin32WindowHandle());
        ImGui_ImplDX11_Init(pDX11Device->GetDXDevice(), pDX11Device->GetDXImmediateContext());
    }
    DX11ImGuiRenderer::~DX11ImGuiRenderer()
    {
        ImGui_ImplDX11_Shutdown();
        ImGui_ImplWin32_Shutdown();
    }
    void DX11ImGuiRenderer::StartRenderingCore()
    {
        ImGui_ImplDX11_NewFrame();
    }
    void DX11ImGuiRenderer::FinalizeRenderingCore(CommandList* pCmdBuffer)
    {
        DX11Swapchain* pSwapchain = (DX11Swapchain*)pCmdBuffer->GetOwnerDevice()->GetSwapchain();

        DX11Device* pDevice = (DX11Device*)GetTargetDevice();
        ID3D11RenderTargetView* pRtv = ((DX11Framebuffer*)pSwapchain->GetFramebuffer())->GetDXRtvs()[0];

        pDevice->LockImmediateContext();
        pDevice->GetDXImmediateContext()->OMSetRenderTargets(1,&pRtv,nullptr);

        ColorRgbaF color = ColorRgbaF::CornflowerBlue();
        pDevice->GetDXImmediateContext()->ClearRenderTargetView(pRtv, &color.R);

        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
        pDevice->UnlockImmediateContext();
    }
    ImGuiTextureBinding* DX11ImGuiRenderer::CreateTextureBinding(TextureResource* pTexture)
    {
        return new DX11ImGuiTextureBinding(pTexture);
    }
}