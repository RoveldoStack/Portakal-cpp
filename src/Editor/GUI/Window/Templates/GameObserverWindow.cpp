#include "GameObserverWindow.h"
#include <Runtime/World/SceneAPI.h>
#include <Runtime/World/Scene.h>
#include <Runtime/World/Aspects/DisplayAspect.h>
#include <Runtime/Resource/RenderTarget/RenderTarget.h>
#include <Runtime/Graphics/Framebuffer.h>
#include <Runtime/Graphics/ResourceTable.h>
#include <Libs/ImGui/imgui.h>
#include <Runtime/Log/Log.h>

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
	}
	void GameObserverWindow::OnFinalize()
	{

	}
	void GameObserverWindow::OnPaint()
	{
		/*
		* Check if scene changed
		*/
		if (SceneAPI::GetPrimalScene() != mTargetScene)
			OnSceneChanged(SceneAPI::GetPrimalScene());

		/*
		* Check if viewport changed
		*/

		/*
		* Draw the buttons
		*/
		if (ImGui::Button("Start"))
		{

		}
		ImGui::SameLine();
		if (ImGui::Button("Stop"))
		{

		}

		/*
		* Render image
		*/
		if (mTargetScene == nullptr)
		{
			ImGui::Text("no primal scene available!");
			return;
		}
		DisplayAspect* pDisplayAspect = mTargetScene->GetAspect<DisplayAspect>();
		if (pDisplayAspect == nullptr)
		{
			ImGui::Text("no display aspect is available for the scene");
			return;
		}
		RenderTarget* pDefaultDisplay = pDisplayAspect->GetDefaultDisplay();
		if (pDefaultDisplay == nullptr)
		{
			CreateDisplay(pDisplayAspect);
			pDefaultDisplay = pDisplayAspect->GetDefaultDisplay();
		}

		ResourceTable* pTable = pDefaultDisplay->GetIsolatedResourceTable();
		const ImVec2 size = ImGui::GetContentRegionAvail();
		ImGui::Image(pTable->GetHandle(), size);
	}
	void GameObserverWindow::OnSceneChanged(Scene* pNewScene)
	{
		mTargetScene = pNewScene;
	}
	void GameObserverWindow::CreateDisplay(DisplayAspect* pAspect)
	{
		/*
		* Create new render target
		*/
		const ImVec2 size = ImGui::GetContentRegionAvail();
		RenderTarget* pRt = new RenderTarget((unsigned int)size.x,(unsigned int)size.y,{TextureFormat::R8_G8_B8_A8_UNorm},TextureFormat::None);

		/*
		* Register it as a display
		*/
		pAspect->RegisterDisplay(pRt);

		LOG("GameObserverWindow", "Display created");
	}
}