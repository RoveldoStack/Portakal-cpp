#include "Scene.h"
#include "SceneAPI.h"
#include <Runtime/World/Entity.h>
#include <Runtime/Resource/ResourceSubObject.h>
#include <Runtime/Resource/ResourceAPI.h>
#include <Runtime/Message/MessageAPI.h>
#include "Aspects/InvalidAspect.h"
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
			for (unsigned int componentIndex = 0; components.GetCursor(); componentIndex++)
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
					if (pFieldType == typeof(ResourceSubObject)) // its an entity
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
			for (unsigned int componentIndex = 0; components.GetCursor(); componentIndex++)
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
						fieldEntry.Type = SceneComponentFieldType::Entity;
					}
					else if (pFieldType->IsSubClassOf(typeof(Component))) // its a component
					{
						fieldEntry.Type = SceneComponentFieldType::Component;
					}
					else if (pFieldType->IsSubClassOf(typeof(ResourceSubObject)))
					{
						fieldEntry.Type = SceneComponentFieldType::Resource;
					}
					else
					{
						// run custom raw content serialization
					}

					componentEntry.Fields.Add(fieldEntry);
				}
			}

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
	void Scene::DestroyCore()
	{
		SceneAPI::RemoveScene(this);
	}
	const Type* GetTypeFromArray(const Array<const Type*>& types, const String& targetTypeName)
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
		Array<const Type*> aspectTypes;
		Array<const Type*> componentTypes;
		for (unsigned int i = 0; i < types.GetCursor(); i++)
		{
			const Type* pType = types[i];

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

			const Type* pType = GetTypeFromArray(aspectTypes, entry.TypeName);
			Type* pFoundType = nullptr;
			if (pType == nullptr) // couldnt found the requested aspect type, create default invalid aspect type!
			{
				pFoundType = typeof(InvalidAspect);
			}

			/*
			* Create aspect
			*/
			SceneAspect* pAspect = CreateAspect(pFoundType);
			if (pType == nullptr) // set intended value if it's an InvalidAspect
			{
				InvalidAspect* pInvalidAspect = (InvalidAspect*)pAspect;
				pInvalidAspect->SetIntendedAspect(entry.TypeName);
			}
		}

		/*
		* Load entities
		*/
		for (unsigned int entityIndex = 0; entityIndex < descriptor.Entities.GetCursor(); entityIndex++)
		{
			const SceneEntityEntry& entityEntry = descriptor.Entities[entityIndex];
		}
	}
}