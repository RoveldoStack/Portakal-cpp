#include "Entity.h"
#include <Runtime/World/Scene.h>

namespace Portakal
{
	Entity::Entity(Scene* pOwnerScene)
	{
		mOwnerScene = pOwnerScene;
	}
	Entity::~Entity()
	{

	}
	Entity::Entity() : mOwnerScene(nullptr)
	{

	}
	Component* Entity::CreateComponent(Type* pType)
	{
		Component* pComponent = (Component*)pType->CreateDefaultHeapObject();
		if (pComponent == nullptr)
			return nullptr;

		pComponent->_SetOwnerEntity(this);
		pComponent->SetTagName(pType->GetTypeName());
		pComponent->OnInitialize();

		mComponents.Add(pComponent);
		return pComponent;
	}
	bool Entity::DeleteComponent(Component* pComponent)
	{
		const int index = mComponents.FindIndex(pComponent);

		if (index == -1)
			return false;

		pComponent->OnFinalize();
		pComponent->Destroy();
		pComponent->_SetOwnerEntity(nullptr);

		return true;
	}

	void Entity::DestroyCore()
	{
		/*
		* Destroy components
		*/
		for (unsigned int i = 0; i < mComponents.GetCursor(); i++)
		{
			Component* pComponent = mComponents[i];

			pComponent->Destroy();
			pComponent->_SetOwnerEntity(nullptr);

			delete pComponent;
		}
		mComponents.Clear();

		/*
		* Notify scene
		*/
		mOwnerScene->_NotifyEntityDeleted(this);
	}
	void Entity::_NotifyComponentDeleted(Component* pComponent)
	{
		const int index = mComponents.FindIndex(pComponent);
		if (index == -1)
			return;

		mComponents.RemoveIndex(index);
	}
}