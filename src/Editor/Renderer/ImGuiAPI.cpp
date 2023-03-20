#include "ImGuiAPI.h"
#include <Runtime/DX12/DX12Device.h>
#include <Libs/ImGui/backends/imgui_impl_dx12.h>
#include <Libs/ImGui/backends/imgui_impl_win32.h>
#include <Runtime/Win32/Win32Window.h>
#include <Runtime/Assert/Assert.h>
#include <Runtime/DXGI/DXGIUtils.h>
#include <Runtime/Graphics/CommandList.h>

namespace Portakal
{
	ImGuiRenderer* ImGuiAPI::sRenderer = nullptr;
}