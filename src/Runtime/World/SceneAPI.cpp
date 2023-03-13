#include "SceneAPI.h"
#include <Runtime/World/Scene.h>

namespace Portakal
{
	SceneAPI* SceneAPI::sAPI = nullptr;

	Scene* SceneAPI::GetPrimalScene()
	{
		if (sAPI == nullptr)
			return nullptr;

		return sAPI->mPrimalScene;
	}
	Array<Scene*> SceneAPI::GetScenes()
	{
		if (sAPI == nullptr)
			return Array<Scene*>();

		return sAPI->mScenes;
	}
	Scene* SceneAPI::CreateScene(const bool bMarkPrimal)
	{
		if (sAPI == nullptr)
			return nullptr;

		return sAPI->CreateSceneInternal(bMarkPrimal);
	}
	Scene* SceneAPI::CreateScene(const SceneDescriptor& descriptor, const bool bMarkPrimal)
	{
		if (sAPI == nullptr)
			return nullptr;

		return sAPI->CreateSceneInternal(descriptor,bMarkPrimal);
	}
	void SceneAPI::MarkScenePrimal(Scene* pScene)
	{
		if (sAPI == nullptr)
			return;

		sAPI->MarkScenePrimalInternal(pScene);
	}
	void SceneAPI::DeleteScene(Scene* pScene)
	{
		if (sAPI == nullptr)
			return;

		sAPI->DeleteSceneInternal(pScene);
	}
	Scene* SceneAPI::CreateSceneInternal(const bool bMarkPrimal)
	{
		if (sAPI == nullptr)
			return nullptr;

		Scene* pScene = new Scene();

		RegisterTargetScene(pScene,bMarkPrimal);

		return pScene;
	}
	Scene* SceneAPI::CreateSceneInternal(const SceneDescriptor& descriptor, const bool bMarkPrimal)
	{
		if (sAPI == nullptr)
			return nullptr;

		Scene* pScene = new Scene(descriptor);

		RegisterTargetScene(pScene, bMarkPrimal);

		return pScene;
	}
	void SceneAPI::MarkScenePrimalInternal(Scene* pScene)
	{
		if (mPrimalScene != nullptr)
		{
			mPrimalScene->_SetPrimalState(false);
			mPrimalScene->_SetActiveState(false);
		}

		pScene->_SetPrimalState(true);
		pScene->_SetActiveState(false);

		mPrimalScene = pScene;
	}
	void SceneAPI::DeleteSceneInternal(Scene* pScene)
	{
		if (sAPI == nullptr || pScene == nullptr)
			return;

		if (mPrimalScene == pScene)
			mPrimalScene = nullptr;

		//TODO: delete scene
		delete pScene;

		mScenes.Remove(pScene);
	}

	SceneAPI::SceneAPI()
	{
		sAPI = this;
		mPrimalScene = nullptr;
	}

	SceneAPI::~SceneAPI()
	{
		sAPI = nullptr;
	}

	void SceneAPI::RegisterTargetScene(Scene* pScene, const bool bMarkPrimal)
	{
		if (bMarkPrimal)
		{
			MarkScenePrimalInternal(pScene);
		}

		mScenes.Add(pScene);
	}
}