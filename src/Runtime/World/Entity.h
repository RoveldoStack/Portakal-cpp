#pragma once
#include <Runtime/Object/TaggedObject.h>
#include <Runtime/World/Component.h>
#include <Runtime/Containers/Array.h>

namespace Portakal
{
	class Scene;

	/// <summary>
	/// Entity is a sub object of the scene, entities can be populated with components to perform various behaviours
	/// </summary>
	PCLASS();
	class PORTAKAL_API Entity : public TaggedObject
	{
		GENERATE_CLASS(Entity);
		friend Scene;
		friend Component;
	public:
		/// <summary>
		/// Returns the owner scene
		/// </summary>
		/// <returns></returns>
		FORCEINLINE Scene* GetOwnerScene() const noexcept { return mOwnerScene; }

		/// <summary>
		/// Returns the owner entity
		/// </summary>
		/// <returns></returns>
		FORCEINLINE Entity* GetOwnerEntity() const noexcept { return mOwnerEntity; }

		/// <summary>
		/// Returns the components
		/// </summary>
		/// <returns></returns>
		FORCEINLINE Array<Component*> GetComponents() const noexcept { return mComponents; }

		/// <summary>
		/// Returns child entities
		/// </summary>
		/// <returns></returns>
		FORCEINLINE Array<Entity*> GetChildEntities() const noexcept { return mChildEntities; }

		/// <summary>
		/// Creates anew component via type
		/// </summary>
		/// <param name="pType"></param>
		/// <returns></returns>
		Component* CreateComponent(Type* pType);

		/// <summary>
		/// Creates anew component via template
		/// </summary>
		template<typename TComponent,typename... TParameters>
		TComponent* CreateComponent(TParameters... parameters)
		{
			TComponent* pComponent = new TComponent(parameters...);

			pComponent->_SetOwnerEntity(this);

			pComponent->OnInitialize();

			mComponents->Add(pComponent);

			return pComponent;
		}

		/// <summary>
		/// Returns a component via template
		/// </summary>
		/// <typeparam name="TComponent"></typeparam>
		/// <returns></returns>
		template<typename TComponent>
		TComponent* GetComponent() const
		{
			Type* pType = TypeAccessor<TComponent>::GetAccessorType();

			for (unsigned int i = 0; i < mComponents.GetCursor(); i++)
			{
				Component* pComponent = mComponents[i];
				if (pComponent->GetType() == pType)
					return (TComponent*)pComponent;
			}

			return nullptr;
		}

		/// <summary>
		/// Returns whether the given template component type exists inside this entity
		/// </summary>
		/// <typeparam name="TComponent"></typeparam>
		/// <returns></returns>
		template<typename TComponent>
		bool HasComponent() const
		{
			Type* pType = TypeAccessor<TComponent>::GetAccessorType();

			for (unsigned int i = 0; i < mComponents.GetCursor(); i++)
			{
				Component* pComponent = mComponents[i];
				if (pComponent->GetType() == pType)
					return true;
			}

			return false;
		}

		/// <summary>
		/// Returns whether it has a component with the same given type
		/// </summary>
		/// <param name="pScene"></param>
		bool HasComponent(const Type* pType)
		{
			for (unsigned int i = 0; i < mComponents.GetCursor(); i++)
			{
				Component* pComponent = mComponents[i];
				if (pComponent->GetType() == pType)
					return true;
			}
			return false;
		}

		/// <summary>
		/// Deletes a component with via given template type
		/// </summary>
		template<typename TComponent>
		bool DeleteComponent()
		{
			const Type* pType = TypeAccessor<TComponent>::GetAccessorType();
			for (unsigned int i = 0; i < mComponents.GetCursor(); i++)
			{
				Component* pComponent = mComponents[i];

				if (pComponent->GetType() == pType)
				{
					pComponent->OnFinalize();
					pComponent->Destroy();
					pComponent->_SetOwnerEntity(nullptr);
					return true;
				}
			}

			return false;
		}

		bool DeleteComponent(Component* pComponent);

		void SetOwnerEntity(Entity* pEntity);
	private:
		Entity(Scene* pScene);
		Entity();
		~Entity();

		Component* _SetDefaultsAndCreateComponent(Type* pComponentType,const String& yamlDefaults);
		void _NotifyComponentDeleted(Component* pComponent);
		void _SetOwnerScene(Scene* pScene) { mOwnerScene = pScene; }

		void OnChildEntityRemoved(Entity* pEntity);
		void OnChildEntityRegistered(Entity* pEntity);

		virtual void DestroyCore() override;
	private:
		Array<Entity*> mChildEntities;
		Array<Component*> mComponents;
		Scene* mOwnerScene;
		Entity* mOwnerEntity;
	};

#include "Entity.reflect.h"

}