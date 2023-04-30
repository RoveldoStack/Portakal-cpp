#include "Scene.h"
#include "SceneAPI.h"
#include <Runtime/World/Entity.h>
#include <Runtime/Resource/ResourceSubObject.h>
#include <Runtime/Resource/ResourceAPI.h>
#include <Runtime/Message/MessageAPI.h>
#include <Runtime/World/Components/InvalidComponent.h>
#include <Runtime/World/Aspects/InvalidAspect.h>

namespace Portakal
{
	Scene::Scene(const SceneDescriptor& descriptor)
	{
		mActive = false;
		mPrimal = false;
		
		CreateFromDescriptor(descriptor);

		SceneAPI::RegisterScene(this);
	}
	Scene::Scene()
	{
		mActive = false;
		mPrimal = false;

		SceneAPI::RegisterScene(this);
	}
	void Scene::GenerateDescriptor(SceneDescriptor& outDescriptor) const noexcept
	{
		/*
		* First of set the given descriptor to its default state
		*/
		outDescriptor = {};

		/*
		* Record resources
		*/
		for (unsigned int entityIndex = 0; entityIndex < mEntities.GetCursor(); entityIndex++)
		{
			const Entity* pEntity = mEntities[entityIndex];

			/*
			* Get and record components
			*/
			const Array<Component*> components = pEntity->GetComponents();
			for (unsigned int componentIndex = 0; componentIndex < components.GetCursor(); componentIndex++)
			{
				const Component* pComponent = components[componentIndex];

				/*
				* Record component field values
				*/
				const Array<Field*> fields = pComponent->GetType()->GetFields();
				for (unsigned int fieldIndex = 0; fieldIndex < fields.GetCursor(); fieldIndex++)
				{
					const Field* pField = fields[fieldIndex];
					if (pField->GetAccessSpecifier() != AccessSpecifier::Public)
						continue;

					const Type* pFieldType = pField->GetFieldType();
					if (pFieldType->IsSubClassOf(typeof(ResourceSubObject))) // its an resource
					{
						ResourceSubObject* pResource = pField->GetValue<ResourceSubObject*>((void*)pComponent);
						if (pResource == nullptr)
							continue;

						outDescriptor.Resources.Add({ pResource->GetID() });
					}
					
				}
			}

		}

		/*
		* Record aspects
		*/
		for (unsigned int i = 0; i < mAspects.GetCursor(); i++)
		{
			const SceneAspect* pAspect = mAspects[i];

			SceneAspectEntry entry = {};
			entry.TypeName = pAspect->GetType()->GetTypeName();

			outDescriptor.Aspects.Add(entry);
		}

		/*
		* Record entities
		*/
		for (unsigned int entityIndex = 0; entityIndex < mEntities.GetCursor(); entityIndex++)
		{
			const Entity* pEntity = mEntities[entityIndex];

			SceneEntityEntry entityEntry = {};
			entityEntry.ID = pEntity->GetID();
			entityEntry.TagName = pEntity->GetTagName();

			/*
			* Get and record components
			*/
			const Array<Component*> components = pEntity->GetComponents();
			for (unsigned int componentIndex = 0; componentIndex < components.GetCursor(); componentIndex++)
			{
				const Component* pComponent = components[componentIndex];

				SceneComponentEntry componentEntry = {};
				componentEntry.ID = pComponent->GetID();
				componentEntry.TagName = pComponent->GetTagName();
				componentEntry.TypeName = pComponent->GetType()->GetTypeName();
				
				/*
				* Record component field values
				*/
				const Array<Field*> fields = pComponent->GetType()->GetFields();
				for (unsigned int fieldIndex = 0; fieldIndex < fields.GetCursor(); fieldIndex++)
				{
					const Field* pField = fields[fieldIndex];
					if (pField->GetAccessSpecifier() != AccessSpecifier::Public)
						continue;

					SceneComponentFieldEntry fieldEntry = {};
					fieldEntry.FieldName = pField->GetFieldName();

					const Type* pFieldType = pField->GetFieldType();
					if (pFieldType == typeof(Entity)) // its an entity
					{
						const Entity* pObject = pField->GetValue<Entity*>((void*)pComponent);
						fieldEntry.Type = SceneComponentFieldType::Entity;
						fieldEntry.Content = Guid::ToString(pObject == nullptr ? Guid::Zero() : pObject->GetID());
					}
					else if (pFieldType->IsSubClassOf(typeof(Component))) // its a component
					{
						const Component* pObject = pField->GetValue<Component*>((void*)pComponent);
						fieldEntry.Type = SceneComponentFieldType::Component;
						fieldEntry.Content = Guid::ToString(pObject == nullptr ? Guid::Zero() : pObject->GetID());
					}
					else if (pFieldType->IsSubClassOf(typeof(ResourceSubObject)))
					{
						const ResourceSubObject* pObject = pField->GetValue<ResourceSubObject*>((void*)pComponent);
						fieldEntry.Type = SceneComponentFieldType::Resource;
						fieldEntry.Content = Guid::ToString(pObject == nullptr ? Guid::Zero() : pObject->GetID());
					}
					else
					{
						fieldEntry.Type = SceneComponentFieldType::Raw;
						//fieldEntry.Content = YamlDefaultSerializer::FieldToYaml(pComponent,pField);
					}

					componentEntry.Fields.Add(fieldEntry);
				}

				entityEntry.Components.Add(componentEntry);
			}

			outDescriptor.Entities.Add(entityEntry);
		}
	}
	Entity* Scene::CreateEntity()
	{
		Entity* pEntity = new Entity(this);

		mEntities.Add(pEntity);

		return pEntity;
	}
	bool Scene::DeleteEntity(Entity* pEntity)
	{
		const int index = mEntities.FindIndex(pEntity);
		if (index == -1)
			return false;

		pEntity->Destroy();
		pEntity->_SetOwnerScene(nullptr);

		return false;
	}
	void Scene::MarkPrimal()
	{
		SceneAPI::ReportPrimal(this);
		mPrimal = true;
	}
	void Scene::SetActivationState(const bool bActive)
	{
		_SetActiveState(bActive);
	}
	void Scene::_OnEntityOwned(Entity* pEntity)
	{
		mEntities.Add(pEntity);
	}
	void Scene::DestroyCore()
	{
		/*
		* Remove aspects
		*/
		for (unsigned int i = 0; i < mAspects.GetCursor(); i++)
		{
			SceneAspect* pAspect = mAspects[i];

			pAspect->OnFinalize();
			pAspect->_SetOnwerScene(nullptr);

			delete pAspect;
		}
		mAspects.Clear();

		/*
		* Remove entities
		*/
		for (unsigned int i = 0; i < mEntities.GetCursor(); i++)
		{
			Entity* pEntity = mEntities[i];

			pEntity->Destroy();
		}
		/*
		* Inform scene api to remove this scene
		*/
		SceneAPI::RemoveScene(this);
	}
	Type* GetTypeFromArray(const Array<Type*>& types, const String& targetTypeName)
	{
		for (unsigned int i = 0; i < types.GetCursor(); i++)
			if (types[i]->GetTypeName() == targetTypeName)
				return types[i];
		return nullptr;
	}
	void Scene::CreateFromDescriptor(const SceneDescriptor& descriptor)
	{
		/*
		* Get all component and aspect types
		*/
		const Array<Type*> types = Assembly::GetProcessAssembly()->GetTypes();
		Array<Type*> aspectTypes;
		Array<Type*> componentTypes;
		for (unsigned int i = 0; i < types.GetCursor(); i++)
		{
			Type* pType = types[i];

			if (pType->IsSubClassOf(typeof(SceneAspect)))
			{
				aspectTypes.Add(pType);
				continue;
			}
			else if (pType->IsSubClassOf(typeof(Component)))
			{
				componentTypes.Add(pType);
			}
		}

		/*
		* Load all the resources
		*/
		Array<Resource*> validLoadedResources;
		for (unsigned int i = 0; i < descriptor.Resources.GetCursor(); i++)
		{
			const SceneResourceEntry& entry = descriptor.Resources[i];

			Resource* pResource = ResourceAPI::GetResourceViaID(entry.ID);
			if (pResource == nullptr)
			{
				MessageAPI::BroadcastMessage("Couldnt find the message");
				continue;
			}

			/*
			* Load
			*/
			pResource->LoadSync();

			validLoadedResources.Add(pResource);
		}

		/*
		* Load aspects
		*/
		for (unsigned int i = 0; i < descriptor.Aspects.GetCursor(); i++)
		{
			const SceneAspectEntry& entry = descriptor.Aspects[i];

			Type* pType = GetTypeFromArray(aspectTypes, entry.TypeName);
			if (pType == nullptr) // couldnt found the requested aspect type, create default invalid aspect type!
			{
				pType = typeof(InvalidAspect);
			}

			/*
			* Create aspect
			*/
			SceneAspect* pAspect = CreateAspect(pType);
			if (pType == typeof(InvalidAspect)) // set intended value if it's an InvalidAspect
			{
				InvalidAspect* pInvalidAspect = (InvalidAspect*)pAspect;
				pInvalidAspect->SetIntendedAspect(entry.TypeName);
			}
		}

		/*
		* Load entities and components
		*/
		for (unsigned int entityIndex = 0; entityIndex < descriptor.Entities.GetCursor(); entityIndex++)
		{
			const SceneEntityEntry& entityEntry = descriptor.Entities[entityIndex];

			Entity* pEntity = CreateEntity();
			pEntity->SetTagName(entityEntry.TagName);
			pEntity->OverrideID(entityEntry.ID);

			/*
			* Load components
			*/
			for (unsigned int componentIndex = 0; componentIndex < entityEntry.Components.GetCursor(); componentIndex++)
			{
				const SceneComponentEntry& componentEntry = entityEntry.Components[componentIndex];

				Type* pComponentType = GetTypeFromArray(componentTypes, componentEntry.TypeName);
				if (pComponentType == nullptr)
				{
					pComponentType = typeof(InvalidComponent);
				}

				/*
				* Create component
				*/
				Component* pComponent = pEntity->CreateComponent(pComponentType);
				if (pComponentType == typeof(InvalidComponent))
				{
					InvalidComponent* pInvalidComponent = (InvalidComponent*)pComponent;
					pInvalidComponent->SetIntendedType(componentEntry.TypeName);
					continue;
				}

				/*
				* Load fields
				*/
				for (unsigned int fieldIndex = 0; fieldIndex < componentEntry.Fields.GetCursor(); fieldIndex++)
				{
					const SceneComponentFieldEntry& fieldEntry = componentEntry.Fields[fieldIndex];

					Field* pField = pComponentType->GetField(fieldEntry.FieldName);

					if (pField == nullptr)
						continue;

					Type* pFieldType = pField->GetFieldType();

					if (pFieldType == nullptr)
						continue;
				}
			}
		}
	}

	void Scene::_NotifyEntityDeleted(Entity* pEntity)
	{
		const int index = mEntities.FindIndex(pEntity);

		if (index == -1)
			return;

		mEntities.RemoveIndex(index);
	}
}