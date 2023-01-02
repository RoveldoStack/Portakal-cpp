#include "SceneAPI.h"
#include <Runtime/World/Scene.h>

namespace Portakal
{
	SceneAPI* SceneAPI::_api = nullptr;

	Scene* SceneAPI::GetPrimalScene()
	{
		if (_api == nullptr)
			return nullptr;

		return _api->_primalScene;
	}
	Array<Scene*> SceneAPI::GetScenes()
	{
		if (_api == nullptr)
			return Array<Scene*>();

		return _api->_scenes;
	}
	Scene* SceneAPI::CreateScene(const bool bMarkPrimal)
	{
		if (_api == nullptr)
			return nullptr;

		return _api->CreateSceneInternal(bMarkPrimal);
	}
	Scene* SceneAPI::CreateScene(const SceneDescriptor& descriptor, const bool bMarkPrimal)
	{
		if (_api == nullptr)
			return nullptr;

		return _api->CreateSceneInternal(descriptor,bMarkPrimal);
	}
	void SceneAPI::MarkScenePrimal(Scene* pScene)
	{
		if (_api == nullptr)
			return;

		_api->MarkScenePrimalInternal(pScene);
	}
	void SceneAPI::DeleteScene(Scene* pScene)
	{
		if (_api == nullptr)
			return;

		_api->DeleteSceneInternal(pScene);
	}
	Scene* SceneAPI::CreateSceneInternal(const bool bMarkPrimal)
	{
		if (_api == nullptr)
			return nullptr;

		Scene* pScene = new Scene();

		RegisterTargetScene(pScene,bMarkPrimal);

		return pScene;
	}
	Scene* SceneAPI::CreateSceneInternal(const SceneDescriptor& descriptor, const bool bMarkPrimal)
	{
		if (_api == nullptr)
			return nullptr;

		Scene* pScene = new Scene(descriptor);

		RegisterTargetScene(pScene, bMarkPrimal);

		return pScene;
	}
	void SceneAPI::MarkScenePrimalInternal(Scene* pScene)
	{
		if (_primalScene != nullptr)
		{
			_primalScene->_SetPrimalState(false);
			_primalScene->_SetActiveState(false);
		}

		_primalScene = pScene;

		pScene->_SetPrimalState(true);
		pScene->_SetActiveState(false);
	}
	void SceneAPI::DeleteSceneInternal(Scene* pScene)
	{
		if (_api == nullptr || pScene == nullptr)
			return;

		if (_primalScene == pScene)
			_primalScene = nullptr;

		//TODO: delete scene

		_scenes.Remove(pScene);
	}

	SceneAPI::SceneAPI()
	{
		_api = this;
	}

	SceneAPI::~SceneAPI()
	{
		_api = nullptr;
	}

	void SceneAPI::RegisterTargetScene(Scene* pScene, const bool bMarkPrimal)
	{
		if (bMarkPrimal)
		{
			MarkScenePrimalInternal(pScene);
		}

		_scenes.Add(pScene);
	}
}