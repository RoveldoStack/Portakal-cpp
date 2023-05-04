#include "SceneAPI.h"
#include <Runtime/World/Scene.h>

namespace Portakal
{
	SceneAPI::SceneAPI() : mPrimalScene(nullptr)
	{

	}
	SceneAPI::~SceneAPI()
	{

	}
	Scene* SceneAPI::GetPrimalScene()
	{
		if (GetUnderlyingAPI() == nullptr)
			return nullptr;

		return GetUnderlyingAPI()->mPrimalScene;
	}
	Array<Scene*> SceneAPI::GetScenes()
	{
		if (GetUnderlyingAPI() == nullptr)
			return {};

		return GetUnderlyingAPI()->mScenes;
	}
	void SceneAPI::RegisterScene(Scene* pScene)
	{
		if (GetUnderlyingAPI() == nullptr)
			return;

		GetUnderlyingAPI()->mScenes.Add(pScene);
	}
	void SceneAPI::RemoveScene(Scene* pScene)
	{
		if (GetUnderlyingAPI() == nullptr)
			return;

		GetUnderlyingAPI()->mScenes.Remove(pScene); 

		if (pScene == GetUnderlyingAPI()->mPrimalScene)
		{
			GetUnderlyingAPI()->mPrimalScene = nullptr;
		}
	}
	void SceneAPI::ReportPrimal(Scene* pScene)
	{
		if (GetUnderlyingAPI() == nullptr)
			return;

		if (GetUnderlyingAPI()->mPrimalScene != nullptr)
		{
			GetUnderlyingAPI()->mPrimalScene->_SetPrimalState(false);
		}

		GetUnderlyingAPI()->mPrimalScene = pScene;
	}
	
}