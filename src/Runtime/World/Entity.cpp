#include "Entity.h"

namespace Portakal
{
	Entity::Entity(Scene* pOwnerScene)
	{
		mOwnerScene = pOwnerScene;
	}
	Entity::~Entity()
	{

	}

	void Entity::DestroyCore()
	{

	}
	Entity::Entity() : mOwnerScene(nullptr)
	{

	}
}