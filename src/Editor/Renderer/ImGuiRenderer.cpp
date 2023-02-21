#include "ImGuiRenderer.h"
#include <Runtime/Graphics/GraphicsDevice.h>
#include <Editor/Renderer/ImGuiAPI.h>
#include <Runtime/Window/Window.h>
#include <Editor/Renderer/DX12ImGuiRenderer.h>
#include <Runtime/Input/Keys.h>
#include <Runtime/Log/Log.h>
#include <Runtime/Window/WindowEvents.h>

namespace Portakal
{
	ImGuiRenderer* ImGuiRenderer::Create(GraphicsDevice* pDevice)
	{
		ImGuiRenderer* pRenderer = nullptr;

		switch (pDevice->GetBackend())
		{
			case Portakal::GraphicsBackend::Directx11:
			{
				break;
			}
			case Portakal::GraphicsBackend::Directx12:
			{
				pRenderer = new DX12ImGuiRenderer(pDevice);
				break;
			}
			case Portakal::GraphicsBackend::Vulkan:
				break;
			default:
				break;
		}

		return pRenderer;
	}
	ImGuiRenderer::ImGuiRenderer(GraphicsDevice* pDevice)
	{
		/*
		* Get window
		*/
		Window* pWindow = pDevice->GetOwnerWindow();

		/*
		* Create context
		*/
		mContext = ImGui::CreateContext();
		ImGui::SetCurrentContext(mContext);

		/*
		* Setup configs
		*/
		ImGuiIO& io = ImGui::GetIO();
		io.BackendFlags = ImGuiBackendFlags_None;
		io.ConfigFlags = ImGuiConfigFlags_DockingEnable; // enables docking

		/*
		* Setup display config
		*/
		io.DisplaySize = ImVec2(pWindow->GetWidth(),pWindow->GetHeight());
		io.DisplayFramebufferScale = ImVec2(1, 1);

		/*
		* Setup special keys
		*/
		io.KeyMap[ImGuiKey_Tab] = PORTAKAL_KEY_TAB;
		io.KeyMap[ImGuiKey_LeftArrow] = PORTAKAL_KEY_LEFT;
		io.KeyMap[ImGuiKey_RightArrow] = PORTAKAL_KEY_RIGHT;
		io.KeyMap[ImGuiKey_UpArrow] = PORTAKAL_KEY_UP;
		io.KeyMap[ImGuiKey_DownArrow] = PORTAKAL_KEY_DOWN;
		io.KeyMap[ImGuiKey_PageUp] = PORTAKAL_KEY_PAGE_UP;
		io.KeyMap[ImGuiKey_PageDown] = PORTAKAL_KEY_PAGE_DOWN;
		io.KeyMap[ImGuiKey_Home] = PORTAKAL_KEY_HOME;
		io.KeyMap[ImGuiKey_End] = PORTAKAL_KEY_END;
		io.KeyMap[ImGuiKey_Insert] = PORTAKAL_KEY_INSERT;
		io.KeyMap[ImGuiKey_Delete] = PORTAKAL_KEY_DELETE;
		io.KeyMap[ImGuiKey_Backspace] = PORTAKAL_KEY_BACKSPACE;
		io.KeyMap[ImGuiKey_Space] = PORTAKAL_KEY_SPACE;
		io.KeyMap[ImGuiKey_Enter] = PORTAKAL_KEY_ENTER;
		io.KeyMap[ImGuiKey_Escape] = PORTAKAL_KEY_ESCAPE;
		io.KeyMap[ImGuiKey_LeftShift] = PORTAKAL_KEY_LEFT_SHIFT;
		io.KeyMap[ImGuiKey_RightShift] = PORTAKAL_KEY_RIGHT_SHIFT;
		io.KeyMap[ImGuiKey_LeftCtrl] = PORTAKAL_KEY_LEFT_CONTROL;
		io.KeyMap[ImGuiKey_RightCtrl] = PORTAKAL_KEY_RIGHT_CONTROL;
		io.KeyMap[ImGuiKey_CapsLock] = PORTAKAL_KEY_CAPS_LOCK;

		/*
		* Setup ascii keyboard mapping
		*/
		for (unsigned int i = 0; i <= PORTAKAL_KEY_Z - PORTAKAL_KEY_A; i++)
		{
			io.KeyMap[ImGuiKey_A + i] = PORTAKAL_KEY_A + i;
		}

		/*
		* Setup numerics
		*/
		for (unsigned int i = 0; i <= PORTAKAL_KEY_9 - PORTAKAL_KEY_0; i++)
		{
			io.KeyMap[ImGuiKey_0 + i] = PORTAKAL_KEY_0 + i;
		}

		/*
		* Setup default theme
		*/
		ImGuiStyle* style = &ImGui::GetStyle();

		style->WindowPadding = ImVec2(15, 15);
		style->WindowRounding = 5.0f;
		style->FramePadding = ImVec2(5, 5);
		style->FrameRounding = 4.0f;
		style->ItemSpacing = ImVec2(12, 8);
		style->ItemInnerSpacing = ImVec2(8, 6);
		style->IndentSpacing = 25.0f;
		style->ScrollbarSize = 15.0f;
		style->ScrollbarRounding = 9.0f;
		style->GrabMinSize = 5.0f;
		style->GrabRounding = 3.0f;

		style->Colors[ImGuiCol_Text] = ImVec4(0.80f, 0.80f, 0.83f, 1.00f);
		style->Colors[ImGuiCol_TextDisabled] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
		style->Colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
		style->Colors[ImGuiCol_PopupBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
		style->Colors[ImGuiCol_Border] = ImVec4(0.80f, 0.80f, 0.83f, 0.88f);
		style->Colors[ImGuiCol_BorderShadow] = ImVec4(0.92f, 0.91f, 0.88f, 0.00f);
		style->Colors[ImGuiCol_FrameBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
		style->Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
		style->Colors[ImGuiCol_FrameBgActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
		style->Colors[ImGuiCol_TitleBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
		style->Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(1.00f, 0.98f, 0.95f, 0.75f);
		style->Colors[ImGuiCol_TitleBgActive] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
		style->Colors[ImGuiCol_MenuBarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
		style->Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
		style->Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
		style->Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
		style->Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
		style->Colors[ImGuiCol_CheckMark] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
		style->Colors[ImGuiCol_SliderGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
		style->Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
		style->Colors[ImGuiCol_Button] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
		style->Colors[ImGuiCol_ButtonHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
		style->Colors[ImGuiCol_ButtonActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
		style->Colors[ImGuiCol_Header] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
		style->Colors[ImGuiCol_HeaderHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
		style->Colors[ImGuiCol_HeaderActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
		style->Colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		style->Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
		style->Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
		style->Colors[ImGuiCol_PlotLines] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
		style->Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
		style->Colors[ImGuiCol_PlotHistogram] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
		style->Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
		style->Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.25f, 1.00f, 0.00f, 0.43f);

		mDevice = pDevice;

	}
	ImGuiRenderer::~ImGuiRenderer()
	{
		ImGui::DestroyContext(mContext);
	}
	ImGuiTextureBinding* ImGuiRenderer::GetOrCreateTextureBinding(TextureResource* pTexture)
	{
		const int index = mTextureBindings.FindIndex(pTexture);

		RegistryEntry<TextureResource*, ImGuiTextureBinding*> entry = {};
		if (index == -1) // create
		{
			ImGuiTextureBinding* pBinding = CreateTextureBinding(pTexture);
			entry = mTextureBindings.Register(pTexture, pBinding);
		}
		else
		{
			entry = mTextureBindings.GetEntryViaIndex(index);
		}

		return entry.Value;
	}
	void ImGuiRenderer::DeleteTextureBinding(TextureResource* pTexture)
	{
		const int index = mTextureBindings.FindIndex(pTexture);
		if (index == -1)
			return;

		RegistryEntry<TextureResource*, ImGuiTextureBinding*> entry = mTextureBindings.GetEntryViaIndex(index);

		mTextureBindings.Remove(pTexture);

		delete entry.Value;
	}
	void ImGuiRenderer::StartRendering(const float deltaTime)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.DeltaTime = deltaTime / 1000.0f;

		StartRenderingCore();
		ImGui::NewFrame();
	}
	void ImGuiRenderer::FinalizeRendering(CommandList* pCmdBuffer)
	{
		ImGui::Render();
		FinalizeRenderingCore(pCmdBuffer);

		ImGuiIO& io = ImGui::GetIO();

		io.ClearInputCharacters();
	}
	void ImGuiRenderer::OnEvent(const WindowEvent* pEvent)
	{
		switch (pEvent->GetEventType())
		{
			case WindowEventType::WindowClosed:
				break;
			case WindowEventType::WindowMoved:
				break;
			case WindowEventType::WindowResized:
				OnWindowResized((WindowResizedEvent*)pEvent);
				break;
			case WindowEventType::KeyboardDown:
				OnKeyboardDown((KeyboardKeyDownEvent*)pEvent);
				break;
			case WindowEventType::KeyboardUp:
				OnKeyboardUp((KeyboardKeyUpEvent*)pEvent);
				break;
			case WindowEventType::MouseButtonDown:
				OnMouseButtonDown((MouseButtonDownEvent*)pEvent);
				break;
			case WindowEventType::MouseButtonUp:
				OnMouseButtonUp((MouseButtonUpEvent*)pEvent);
				break;
			case WindowEventType::MouseMoved:
				OnMouseMoved((MouseMovedEvent*)pEvent);
				break;
			case WindowEventType::MouseScrolled:
				OnMouseWheel((MouseWheelEvent*)pEvent);
				break;
			case WindowEventType::Char:
				OnKeyboardChar((KeyboardCharEvent*)pEvent);
				break;
			default:
				break;
		}
	}
	GraphicsBackend ImGuiRenderer::GetTargetBackend() const noexcept
	{
		return mDevice->GetBackend();
	}
	void ImGuiRenderer::OnWindowResized(const WindowResizedEvent* pEvent)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2(pEvent->GetWidth(), pEvent->GetHeight());
	}
	void ImGuiRenderer::OnMouseMoved(const MouseMovedEvent* pEvent)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MousePos = ImVec2(pEvent->GetX(), pEvent->GetY());
	}
	void ImGuiRenderer::OnMouseButtonDown(const MouseButtonDownEvent* pEvent)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[pEvent->GetButton()] = true;

		LOG("Imgui", "Mouse down: %d", pEvent->GetButton());
	}
	void ImGuiRenderer::OnMouseButtonUp(const MouseButtonUpEvent* pEvent)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[pEvent->GetButton()] = false;
		LOG("Imgui", "Mouse up: %d", pEvent->GetButton());
	}
	void ImGuiRenderer::OnMouseWheel(const MouseWheelEvent* pEvent)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseWheel += pEvent->GetVertical();
	}
	void ImGuiRenderer::OnKeyboardDown(const KeyboardKeyDownEvent* pEvent)
	{
		ImGuiIO& io = ImGui::GetIO();

		io.KeysDown[pEvent->GetKey()] = true;
		io.KeyCtrl = io.KeysDown[PORTAKAL_KEY_LEFT_CONTROL] || io.KeysDown[PORTAKAL_KEY_RIGHT_CONTROL];
		io.KeyShift = io.KeysDown[PORTAKAL_KEY_LEFT_SHIFT] || io.KeysDown[PORTAKAL_KEY_RIGHT_SHIFT];
		io.KeyAlt = io.KeysDown[PORTAKAL_KEY_LEFT_ALT] || io.KeysDown[PORTAKAL_KEY_RIGHT_ALT];
		io.KeySuper = io.KeysDown[PORTAKAL_KEY_LEFT_SUPER] || io.KeysDown[PORTAKAL_KEY_RIGHT_SUPER];
	}
	void ImGuiRenderer::OnKeyboardUp(const KeyboardKeyUpEvent* pEvent)
	{
		ImGuiIO& io = ImGui::GetIO();

		io.KeysDown[pEvent->GetKey()] = false;
	}
	void ImGuiRenderer::OnKeyboardChar(const KeyboardCharEvent* pEvent)
	{
		ImGuiIO& io = ImGui::GetIO();

		io.AddInputCharacter(pEvent->GetChar());
	}
}