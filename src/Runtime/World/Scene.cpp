#include "Scene.h"
#include "SceneAPI.h"
#include <Runtime/World/Entity.h>

namespace Portakal
{
	Scene::Scene(const SceneDescriptor& descriptor)
	{
		mActive = false;
		mPrimal = false;
	}
	Scene::Scene()
	{
		mActive = false;
		mPrimal = false;
	}
	Entity* Scene::CreateEntity()
	{
		Entity* pEntity = new Entity(this);

		mEntities.Add(pEntity);

		return pEntity;
	}
	bool Scene::DeleteEntity(Entity* pEntity)
	{
		return false;
	}
	void Scene::MarkPrimal()
	{
		SceneAPI::MarkScenePrimal(this);
	}
	void Scene::DestroyCore()
	{
	}
}