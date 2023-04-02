#include "GameObserverWindow.h"
#include <Runtime/World/SceneAPI.h>
#include <Runtime/World/Scene.h>
#include <Runtime/World/Aspects/DisplayAspect.h>
#include <Runtime/Resource/RenderTarget/RenderTarget.h>
#include <Runtime/Graphics/Framebuffer.h>
#include <Runtime/Graphics/ResourceTable.h>
#include <Libs/ImGui/imgui.h>
#include <Runtime/Log/Log.h>
#include <Editor/Resource/EditorImageResource.h>
#include <Editor/Renderer/ImGuiAPI.h>
#include <Editor/Renderer/ImGuiRenderer.h>
#include <Editor/Renderer/ImGuiTextureBinding.h>

namespace Portakal
{
	void GameObserverWindow::OnShow()
	{

	}
	void GameObserverWindow::OnHide()
	{

	}
	void GameObserverWindow::OnInitialize()
	{
		mTargetScene = nullptr;
		mCurrentSelectedTargetIndex = 0;
	}
	void GameObserverWindow::OnFinalize()
	{

	}
	void GameObserverWindow::OnPaint()
	{
		/*
		* Render image
		*/
		const ImVec2 availSpace = ImGui::GetContentRegionAvail();
		const ImVec2 rectMinPos = ImGui::GetCursorScreenPos();
		const ImVec2 rectMaxPos = { rectMinPos.x + availSpace.x,rectMinPos.y + availSpace.y };
		
		/*
		* Check if scene changed
		*/
		if (SceneAPI::GetPrimalScene() != mTargetScene)
			OnSceneChanged(SceneAPI::GetPrimalScene());

		/*
		* Check if there was a resize request from the last frame
		*/
		if (mHasResizeRequest)
			OnResize();

		/*
		* Check if viewport changed
		*/
		const Vector2UI currentSize = { (unsigned int)ImGui::GetContentRegionAvail().x,(unsigned int)ImGui::GetContentRegionAvail().y };
		if (currentSize != mLastViewportSize)
			OnViewportChanged(currentSize);

		/*
		* Validate if there's an primal scene
		*/
		if (mTargetScene == nullptr)
		{
			const ImVec2 middlePos = { (ImGui::GetCursorPos().x + availSpace.x / 2.0f) - ImGui::CalcTextSize("No primal scene available").x / 2.0f,ImGui::GetCursorPos().y + availSpace.y / 2.0f };
			ImGui::GetWindowDrawList()->AddRectFilled(rectMinPos,rectMaxPos,ImGui::ColorConvertFloat4ToU32({0,0,0,1}));
			ImGui::SetCursorPos(middlePos);
			ImGui::Text("No primal scene available!");
			return;
		}

		/*
		* Validate if there is a display aspect
		*/
		DisplayAspect* pDisplayAspect = mTargetScene->GetAspect<DisplayAspect>();
		if (pDisplayAspect == nullptr)
		{
			const ImVec2 middlePos = { (ImGui::GetCursorPos().x + availSpace.x / 2.0f) - ImGui::CalcTextSize("No display aspect available").x / 2.0f,ImGui::GetCursorPos().y + availSpace.y / 2.0f };
			ImGui::GetWindowDrawList()->AddRectFilled(rectMinPos, rectMaxPos, ImGui::ColorConvertFloat4ToU32({ 0,0,0,1 }));
			ImGui::SetCursorPos(middlePos);
			ImGui::Text("No display aspect available");
			return;
		}

		/*
		* Check if display changed
		*/
		RenderTarget* pDefaultDisplay = pDisplayAspect->GetDefaultDisplay();
		if (pDefaultDisplay != mCurrentDisplay)
			OnDisplayChanged(pDefaultDisplay);

		/*
		* Check if there is no default display!
		*/
		if (pDefaultDisplay == nullptr)
		{
			const ImVec2 middlePos = { (ImGui::GetCursorPos().x + availSpace.x / 2.0f) - ImGui::CalcTextSize("No display render target available").x / 2.0f,ImGui::GetCursorPos().y + availSpace.y / 2.0f };
			ImGui::GetWindowDrawList()->AddRectFilled(rectMinPos, rectMaxPos, ImGui::ColorConvertFloat4ToU32({ 0,0,0,1 }));
			ImGui::SetCursorPos(middlePos);
			ImGui::Text("No display render target available");
			return;
		}

		/*
		* Draw available render targets
		*/
		ImGui::Text("Targets:");
		ImGui::SameLine();
		ImGui::SetNextItemWidth(150);
		if (ImGui::BeginCombo("##comboTargets",*mCurrentTargets[mCurrentSelectedTargetIndex]->GetTagName()))
		{
			for (unsigned int i = 0; i < mCurrentTargets.GetCursor(); i++)
			{
				TextureResource* pTarget = mCurrentTargets[i];
				if (ImGui::Selectable(*pTarget->GetTagName()))
				{
					mCurrentSelectedTargetIndex = i;
				}
			}
			ImGui::EndCombo();
		}
		/*
		* Draw the current render target
		*/
		ImGuiTextureBinding* pBinding = ImGuiAPI::GetDefaultRenderer()->GetOrCreateTextureBinding(mCurrentTargets[mCurrentSelectedTargetIndex]);
		const ImVec2 size = ImGui::GetContentRegionAvail();
		ImGui::Image(pBinding->GetBinding(), size);
	}
	void GameObserverWindow::OnSceneChanged(Scene* pNewScene)
	{
		mCurrentDisplay = nullptr;
		mCurrentSelectedTargetIndex = 0;
		mCurrentTargets.Clear();
		mTargetScene = pNewScene;
		mHasResizeRequest = false;
	}
	void GameObserverWindow::OnViewportChanged(const Vector2UI newSize)
	{
		mLastViewportSize = newSize;
		mHasResizeRequest = true;

		LOG("GameObserverWindow", "Viewport changed");
	}
	void GameObserverWindow::OnDisplayChanged(RenderTarget* pDisplay)
	{
		/*
		* Clear current display imgui bindings
		*/
		ClearCurrentDisplayBindings();

		mCurrentSelectedTargetIndex = 0;
		mCurrentDisplay = pDisplay;

		/*
		* Register targets
		*/
		GetCurrentTargets();
	}
	void GameObserverWindow::OnResize()
	{
		if (mCurrentDisplay == nullptr)
			return;

		LOG("GameObserverWindow", "Resize!");

		/*
		* Clear current display target imgui bindings
		*/
		ClearCurrentDisplayBindings();

		/*
		* Resize
		*/
		mCurrentDisplay->Resize(mLastViewportSize.X, mLastViewportSize.Y);

		/*
		* Get current targets
		*/
		GetCurrentTargets();

		mHasResizeRequest = false;
	}
	void GameObserverWindow::ClearCurrentDisplayBindings()
	{
		if (mCurrentDisplay == nullptr)
			return;

		/*
		* Clear current display target imgui bindings
		*/
		const Array<TextureResource*> colorTargets = mCurrentDisplay->GetColorTargets();
		TextureResource* pDepthStencilTarget = mCurrentDisplay->GetDepthStencilTarget();

		for (unsigned int i = 0; i < colorTargets.GetCursor(); i++)
		{
			TextureResource* pTexture = colorTargets[i];
			ImGuiAPI::GetDefaultRenderer()->DeleteTextureBinding(pTexture);
		}
		if (pDepthStencilTarget != nullptr)
			ImGuiAPI::GetDefaultRenderer()->DeleteTextureBinding(pDepthStencilTarget);
	}
	void GameObserverWindow::GetCurrentTargets()
	{
		mCurrentTargets.Clear();

		mCurrentTargets = mCurrentDisplay->GetColorTargets();
		if (mCurrentDisplay->GetDepthStencilTarget() != nullptr)
			mCurrentTargets.Add(mCurrentDisplay->GetDepthStencilTarget());
	}
}