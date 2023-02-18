#include "WorldObserverWindow.h"
#include <Runtime/World/Scene.h>
#include <Runtime/World/SceneAPI.h>
#include <Runtime/World/Entity.h>
#include <Libs/ImGui/imgui.h>

namespace Portakal
{
	void WorldObserverWindow::OnShow()
	{

	}
	void WorldObserverWindow::OnHide()
	{

	}
	void WorldObserverWindow::OnInitialize()
	{

	}
	void WorldObserverWindow::OnFinalize()
	{

	}
	void WorldObserverWindow::OnPaint()
	{
		/*
		* Check if scene changed
		*/
		if (mTargetScene != SceneAPI::GetPrimalScene())
			OnSceneChanged(SceneAPI::GetPrimalScene());

		/*
		* Validate if target scene is empty
		*/
		if (mTargetScene == nullptr)
		{
			ImGui::Text("No primal scene to observe!");
			return;
		}

		/*
		* Render
		*/
		RenderScene(mTargetScene);
	}
	void WorldObserverWindow::OnSceneChanged(Scene* pNewScene)
	{
		mTargetScene = pNewScene;
	}
	void WorldObserverWindow::RenderScene(Scene* pScene)
	{
		/*
		* Draw header
		*/
		ImGui::Text(*mTargetScene->GetTagName());
		ImGui::Separator();
		ImGui::Spacing();

		/*
		* Draw aspects
		*/
		if (ImGui::CollapsingHeader("Aspects"))
		{

		}

		/*
		* Draw entites
		*/
		if (ImGui::CollapsingHeader("Entities"))
		{
			const Array<Entity*> entities = pScene->GetEntities();

			for (unsigned int i = 0; i < entities.GetCursor(); i++)
			{
				const Entity* pEntity = entities[i];

				ImGui::Selectable(*pEntity->GetTagName());
			}
		}

		/*
		* Handle pre events
		*/
		if (ImGui::IsWindowFocused() && ImGui::IsMouseClicked(ImGuiMouseButton_Right))
		{
			ImGui::OpenPopup("SceneCreateContext");
		}

		/*
		* Handle popups
		*/
		if (ImGui::BeginPopup("SceneCreateContext"))
		{
			if (ImGui::Selectable("Empty entity"))
			{
				Entity* pEntity = pScene->CreateEntity();
				pEntity->SetTagName("Empty entity");
			}

			ImGui::EndPopup();
		}
	}
}