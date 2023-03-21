#include "WorldObserverWindow.h"
#include <Runtime/World/Scene.h>
#include <Runtime/World/SceneAPI.h>
#include <Runtime/World/Entity.h>
#include <Runtime/World/SceneAspect.h>
#include <Libs/ImGui/imgui.h>
#include <Runtime/World/Aspects/SpriteRendererAspect.h>
#include <Editor/Game/EditorGameAPI.h>
#include <Runtime/Resource/Resource.h>
#include <Runtime/Resource/ResourceAPI.h>
#include <Runtime/Log/Log.h>
#include <Editor/Domain/DomainAPI.h>
#include <Editor/Domain/DomainFile.h>
#include <Editor/GUI/Object/EditorObjectAPI.h>
#include <Editor/GUI/Object/Templates/EntityObjectVisualizer.h>

namespace Portakal
{
	Array<WorldObserverWindow*> WorldObserverWindow::sWindows;

	void WorldObserverWindow::SignalSceneChanged(Scene* pScene)
	{
		if (pScene->IsPrimal() && EditorGameAPI::GetCurrentState() != EditorGameState::Idle)
			return;

		for (unsigned int i = 0; i < sWindows.GetCursor(); i++)
		{
			if(sWindows[i]->mTargetScene == pScene)
				sWindows[i]->OnSceneContentChanged();
		}
	}
	void WorldObserverWindow::SignalSceneSaved(Scene* pScene)
	{
		for (unsigned int i = 0; i < sWindows.GetCursor(); i++)
		{
			WorldObserverWindow* pWindow = sWindows[i];

			if (pWindow->mTargetScene == pScene)
				pWindow->mSceneContentChanged = false;
		}
	}
	void WorldObserverWindow::OnShow()
	{

	}
	void WorldObserverWindow::OnHide()
	{

	}
	void WorldObserverWindow::OnInitialize()
	{
		sWindows.Add(this);

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
		sWindows.Remove(this);
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
	void WorldObserverWindow::OnSceneContentChanged()
	{
		mSceneContentChanged = true;
	}
	void WorldObserverWindow::SaveScene()
	{
		/*
		* Get scene resource if any
		*/
		DomainFile* pFile = DomainAPI::GetFileViaID(mTargetScene->GetID());
		if (pFile == nullptr)
		{
			LOG("WorldObserverWindow", "No domain file");
			return;
		}

		/*
		* Save
		*/
		pFile->SaveSync();

		mSceneContentChanged = false;
		SignalSceneSaved(mTargetScene);
	}
	void WorldObserverWindow::RenderScene(Scene* pScene)
	{
		/*
		* Draw header
		*/
		const String title = mTargetScene->GetTagName() + (mSceneContentChanged ? "*" : "");
		ImGui::Text(*title);
		ImGui::SameLine();
		if (mSceneContentChanged)
		{
			if (ImGui::Button("Save"))
			{
				SaveScene();
			}
		}
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
				Entity* pEntity = entities[i];

				if (ImGui::Selectable(*(pEntity->GetTagName() + "##" + Guid::ToString(pEntity->GetID())))) // if selected
				{
					LOG("WorldObjserverWindow", "Entity selected!");
					EditorObjectAPI::SignalNewObject(pEntity);
				}
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
				WorldObserverWindow::SignalSceneChanged(pScene);
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