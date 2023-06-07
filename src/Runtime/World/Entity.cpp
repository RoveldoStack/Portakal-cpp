#include "Entity.h"
#include <Runtime/World/Scene.h>
#include <Runtime/Yaml/YamlDefaultSerializer.h>

namespace Portakal
{
	Entity::Entity(Scene* pOwnerScene)
	{
		mOwnerScene = pOwnerScene;
		mOwnerEntity = nullptr;
	}
	Entity::~Entity()
	{
		mOwnerScene = nullptr;
		mOwnerEntity = nullptr;
	}
	Entity::Entity()
	{
		mOwnerEntity = nullptr;
		mOwnerScene = nullptr;
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

	void Entity::SetOwnerEntity(Entity* pEntity)
	{
		/*
		* Check if we have a former owner entity
		*/
		if (mOwnerEntity != nullptr)
		{
			mOwnerEntity->OnChildEntityRemoved(this);
		}

		/*
		* Check if we assing this entity to another entity or to empty(to scene)
		*/
		if (pEntity == nullptr)
		{
			mOwnerScene->_OnEntityOwned(this);
		}
		else
		{
			pEntity->OnChildEntityRegistered(this);
		}

		mOwnerEntity = pEntity;
	}

	void Entity::OnChildEntityRemoved(Entity* pEntity)
	{
		mChildEntities.Remove(pEntity);
	}

	void Entity::OnChildEntityRegistered(Entity* pEntity)
	{
		mChildEntities.Remove(pEntity);
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
		* Destroy child entities
		*/
		for (unsigned int i = 0; i < mChildEntities.GetCursor(); i++)
		{
			Entity* pEntity = mChildEntities[i];

			pEntity->Destroy();
			
			delete pEntity;
		}
		mChildEntities.Clear();

		/*
		* Notify scene
		*/
		mOwnerScene->_NotifyEntityDeleted(this);
	}
	

	Component* Entity::_SetDefaultsAndCreateComponent(Type* pComponentType, const String& yamlDefaults)
	{
		/*
		* Create component default object
		*/
		Component* pComponent = (Component*)pComponentType->CreateDefaultHeapObject();

		/*
		* Set component values
		*/
		YamlDefaultSerializer::ToObject(yamlDefaults,pComponent, pComponentType);

		/*
		* Register this component to the entity's body
		*/
		pComponent->_SetOwnerEntity(this);
		pComponent->SetTagName(pComponent->GetType()->GetTypeName());
		pComponent->OnInitialize();

		mComponents.Add(pComponent);

		return pComponent;
	}
	void Entity::_NotifyComponentDeleted(Component* pComponent)
	{
		const int index = mComponents.FindIndex(pComponent);
		if (index == -1)
			return;

		mComponents.RemoveIndex(index);
	}
}