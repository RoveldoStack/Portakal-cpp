#include "WorldObserverWindow.h"
#include <Runtime/World/Scene.h>
#include <Runtime/World/SceneAPI.h>
#include <Runtime/World/Entity.h>
#include <Runtime/World/SceneAspect.h>
#include <Libs/ImGui/imgui.h>
#include <Runtime/World/Aspects/SpriteRendererAspect.h>

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
		/*
		* Collect aspects
		*/
		const Array<Type*> allTypes = Assembly::GetProcessAssembly()->GetTypes();
		for (unsigned int i = 0; i < allTypes.GetCursor(); i++)
		{
			Type* pType = allTypes[i];

			if (pType->IsSubClassOf(typeof(SceneAspect)))
			{
				mAvailableAspects.Add(pType);
			}
		}
	}
	void WorldObserverWindow::OnFinalize()
	{
		mAvailableAspects.Clear();
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
			//Draw aspects
			const Array<SceneAspect*> aspects = pScene->GetAspects();
			for (unsigned int i = 0; i < aspects.GetCursor(); i++)
			{
				const SceneAspect* pAspect = aspects[i];

				ImGui::Selectable(*pAspect->GetType()->GetTypeName());
			}

			//Draw register aspect button
			if (mAvailableAspects.GetCursor() > 0)
			{
				if (ImGui::Button("+"))
				{
					ImGui::OpenPopup("CreateAspectContext");
				}
			}
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
		if (ImGui::BeginPopup("CreateAspectContext"))
		{
			for (unsigned int i = 0; i < mAvailableAspects.GetCursor(); i++)
			{
				const Type* pType = mAvailableAspects[i];

				if (ImGui::Selectable(*pType->GetTypeName()))
				{
					mTargetScene->CreateAspect(pType);
				}
			}

			ImGui::EndPopup();
		}
	}
}