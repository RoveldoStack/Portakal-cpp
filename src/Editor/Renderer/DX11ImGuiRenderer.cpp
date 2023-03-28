#include "DX11ImGuiRenderer.h"
#include <Runtime/Win32/Win32Window.h>
#include <Runtime/DX11/DX11Device.h>
#include <Editor/Renderer/DX11ImGuiTextureBinding.h>
#include <Libs/ImGui/backends/imgui_impl_dx11.h>
#include <Libs/ImGui/backends/imgui_impl_win32.h>
#include <Runtime/Graphics/CommandList.h>
#include <Runtime/Graphics/Swapchain.h>

namespace Portakal
{
    DX11ImGuiRenderer::DX11ImGuiRenderer(GraphicsDevice* pDevice) : ImGuiRenderer(pDevice)
    {
        DX11Device* pDX11Device = (DX11Device*)pDevice;

        ImGui_ImplWin32_Init(((Win32Window*)pDevice->GetOwnerWindow())->GetWin32WindowHandle());
        ImGui_ImplDX11_Init(pDX11Device->GetDXDevice(), pDX11Device->GetDXContext());
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
        Swapchain* pSwapchain = pCmdBuffer->GetOwnerDevice()->GetSwapchain();

        pCmdBuffer->BindFramebuffer(pSwapchain->GetFramebuffer());
        pCmdBuffer->ClearColor(0, ColorRgba::DarkGreen());

        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
    }
    ImGuiTextureBinding* DX11ImGuiRenderer::CreateTextureBinding(TextureResource* pTexture)
    {
        return new DX11ImGuiTextureBinding(pTexture);
    }
}