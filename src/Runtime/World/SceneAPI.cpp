#include "SceneAPI.h"
#include <Runtime/World/Scene.h>

namespace Portakal
{
	Array<Scene*> SceneAPI::sScenes;
	Scene* SceneAPI::sPrimalScene = nullptr;

	Scene* SceneAPI::GetPrimalScene()
	{
		return sPrimalScene;
	}
	Array<Scene*> SceneAPI::GetScenes()
	{
		return sScenes;
	}
	void SceneAPI::RegisterScene(Scene* pScene)
	{
		sScenes.Add(pScene);
	}
	void SceneAPI::RemoveScene(Scene* pScene)
	{
		sScenes.Remove(pScene);

		if (pScene == sPrimalScene)
		{
			sPrimalScene = nullptr;
		}
	}
	void SceneAPI::ReportPrimal(Scene* pScene)
	{
		if (sPrimalScene != nullptr)
		{
			sPrimalScene->_SetPrimalState(false);
		}
		sPrimalScene = pScene;
	}
}