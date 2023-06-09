#include "ImGuiRenderer.h"
#include <Runtime/Graphics/GraphicsDevice.h>
#include <Editor/Renderer/ImGuiAPI.h>
#include <Runtime/Window/Window.h>
#include <Runtime/Input/Keys.h>
#include <Runtime/Log/Log.h>
#include <Runtime/Window/WindowEvents.h>
#include <Runtime/Platform/PlatformClipboard.h>
#include <Editor/Renderer/ImGuiKeys.h>
#include <Runtime/HLSL/HLSLCompiler.h>
#include <Runtime/Graphics/Shader/Shader.h>
#include <Runtime/Graphics/Pipeline/Pipeline.h>
#include <Runtime/Assert/Assert.h>
#include <Runtime/Resource/Texture/TextureResource.h>
#include <Runtime/Graphics/Sampler/Sampler.h>
#include <Runtime/Graphics/Buffer/GraphicsBuffer.h>,
#include <Runtime/Graphics/Resource/ResourceTable.h>
#include <Runtime/Graphics/Command/CommandList.h>
#include <Runtime/Object/GarbageCollector.h>
#include <Editor/Renderer/ImGuiTextureBinding.h>
#include <Runtime/Math/Vector2F.h>
#include <Runtime/Rendering/RenderGraph.h>
#include <Runtime/Rendering/Passes/RenderTargetClearColorPass.h>
#include <Runtime/Resource/RenderTarget/RenderTargetResource.h>
#include <Runtime/Resource/Sampler/SamplerResource.h>
#include <Runtime/Resource/Mesh/MeshResource.h>
#include <Runtime/Resource/Shader/ShaderResource.h>
#include <Editor/Renderer/ImGuiRenderPass.h>

namespace Portakal
{
	
	

	
	void SetClipboardTextCallback(void* pUserData,const char* pText)
	{
		PlatformClipboard::SetClipboard(pText);
	}
	const char* GetClipboardTextCallback(void* pUserData)
	{
		return PlatformClipboard::GetClipboard().GetSourceCopy();
	}
	ImGuiRenderer::ImGuiRenderer(GraphicsDevice* pDevice) : 
		mDevice(nullptr), mCmdList(nullptr),mRenderGraph(nullptr),mRenderTarget(nullptr)
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
		* Setup clipboard
		*/
		io.SetClipboardTextFn = SetClipboardTextCallback;
		io.GetClipboardTextFn = GetClipboardTextCallback;

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

		/*
		* Create imgui device resources...
		*/

	
		
		/*
		* Create dummy render graph
		*/
		mRenderTarget = new RenderTargetResource(pDevice->GetSwapchain());
		mRenderGraph = new RenderGraph();

		/*
		* Create globals
		*/
		mRenderGraph->CreateGlobalRenderTarget("ImGuiRenderTarget");


		/*
		* Set global data
		*/
		mRenderGraph->SetGlobalRenderTarget("ImGuiRenderTarget", mRenderTarget);

		/*
		* Create render passes
		*/
		ImGuiRenderPass* pImGuiPass = mRenderGraph->CreatePass<ImGuiRenderPass>();
		mRenderGraph->GetGlobalIO("ImGuiRenderTarget")->ConnectOutputTo(pImGuiPass, "rtIn");


		/*
		* Setup finish pass
		*/
		mRenderGraph->SetFinishPass(pImGuiPass);

		/*
		* Compile render graph
		*/
		mRenderGraph->Compile();

		mCmdList = pDevice->CreateCommandList({});
		mDevice = pDevice;
	}
	ImGuiRenderer::~ImGuiRenderer()
	{
		/*
		* Delete resources
		*/

		mCmdList->Destroy();
		mRenderGraph->Destroy();

		mCmdList = nullptr;
		mDevice = nullptr;
		mRenderGraph = nullptr;

		GarbageCollector::Collect();

		/*
		* Delete context
		*/
		ImGui::DestroyContext(mContext);
	}
	ImGuiTextureBinding* ImGuiRenderer::GetOrCreateTextureBinding(TextureResource* pTexture)
	{
		/*
		* Try get index of the texture
		*/
		const int index = mTextureBindings.FindIndex(pTexture);

		if (index == -1) // create
		{
			ImGuiTextureBinding* pBinding = new ImGuiTextureBinding(pTexture);
			mTextureBindings.Register(pTexture, pBinding);

			return pBinding;
		}
		else
		{
			return mTextureBindings[index].Value;
		}

		return nullptr;
	}
	void ImGuiRenderer::DeleteTextureBinding(TextureResource* pTexture)
	{
		const int index = mTextureBindings.FindIndex(pTexture);
		if (index == -1)
			return;

		/*
		* Get and delete
		*/
		RegistryEntry<TextureResource*, ImGuiTextureBinding*>& entry = mTextureBindings[index];
		delete entry.Value;
		entry.Value = nullptr;

		mTextureBindings.Remove(pTexture);
	}
	void ImGuiRenderer::StartRendering(const float deltaTime)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.DeltaTime = deltaTime / 1000.0f;
		io.DisplaySize = { (float)mDevice->GetOwnerWindow()->GetWidth(),(float)mDevice->GetOwnerWindow()->GetHeight() };

		ImGui::NewFrame();
	}

	void ImGuiRenderer::FinalizeRendering(Framebuffer* pFramebuffer)
	{
		ImGuiIO& io = ImGui::GetIO();

		/*
		* Render imgui
		*/
		ImGui::Render();

		/*
		* Execute imgui render graph
		*/
		mCmdList->Lock();
		mRenderGraph->ExecuteSync(mCmdList);
		mCmdList->Unlock();

		/*
		* Submit commands and wait
		*/
		mDevice->SubmitCommands(mCmdList);
		mDevice->WaitForFinish();
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
		io.AddMousePosEvent(pEvent->GetX(), pEvent->GetY());
	}
	void ImGuiRenderer::OnMouseButtonDown(const MouseButtonDownEvent* pEvent)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.AddMouseButtonEvent(pEvent->GetButton(), true);
	}
	void ImGuiRenderer::OnMouseButtonUp(const MouseButtonUpEvent* pEvent)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.AddMouseButtonEvent(pEvent->GetButton(), false);
	}
	void ImGuiRenderer::OnMouseWheel(const MouseWheelEvent* pEvent)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.AddMouseWheelEvent(0, pEvent->GetVertical() > 0 ? 1 : -1);
	}
	void ImGuiRenderer::OnKeyboardDown(const KeyboardKeyDownEvent* pEvent)
	{
		ImGuiIO& io = ImGui::GetIO();

		io.AddKeyEvent(ImGuiKeys::GetKey(pEvent->GetKey()), true);

		if(pEvent->GetKey() == KeyboardKeys::LeftControl)
			io.AddKeyEvent(ImGuiKey_ModCtrl, true);
		if (pEvent->GetKey() == KeyboardKeys::LeftShift)
			io.AddKeyEvent(ImGuiKey_ModShift,true);
		if (pEvent->GetKey() == KeyboardKeys::LeftShift)
			io.AddKeyEvent(ImGuiKey_ModAlt, true);
		if (pEvent->GetKey() == KeyboardKeys::LeftShift)
			io.AddKeyEvent(ImGuiKey_ModSuper, true);
	}
	void ImGuiRenderer::OnKeyboardUp(const KeyboardKeyUpEvent* pEvent)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.AddKeyEvent(ImGuiKeys::GetKey(pEvent->GetKey()),false);

		if (pEvent->GetKey() == KeyboardKeys::LeftControl)
			io.AddKeyEvent(ImGuiKey_ModCtrl, false);
		if (pEvent->GetKey() == KeyboardKeys::LeftShift)
			io.AddKeyEvent(ImGuiKey_ModShift, false);
		if (pEvent->GetKey() == KeyboardKeys::LeftShift)
			io.AddKeyEvent(ImGuiKey_ModAlt, false);
		if (pEvent->GetKey() == KeyboardKeys::LeftShift)
			io.AddKeyEvent(ImGuiKey_ModSuper, false);
	}
	void ImGuiRenderer::OnKeyboardChar(const KeyboardCharEvent* pEvent)
	{
		ImGuiIO& io = ImGui::GetIO();

		io.AddInputCharacter(pEvent->GetChar());
	}
}