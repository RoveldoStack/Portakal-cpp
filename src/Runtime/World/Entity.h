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
	class PORTAKAL_API Entity : public TaggedObject
	{
		friend Scene;
	public:

		/// <summary>
		/// Returns the owner scene
		/// </summary>
		/// <returns></returns>
		FORCEINLINE Scene* GetOwnerScene() const noexcept { return mOwnerScene; }

		/// <summary>
		/// Returns the components
		/// </summary>
		/// <returns></returns>
		FORCEINLINE Array<Component*> GetComponents() const noexcept { return mComponents; }

		/// <summary>
		/// Creates anew component via type
		/// </summary>
		/// <param name="pType"></param>
		/// <returns></returns>
		Component* CreateComponent(Type* pType)
		{
			Component* pComponent = (Component*)pType->CreateDefaultHeapObject();
			if (pComponent == nullptr)
				return nullptr;

			pComponent->_SetOwnerEntity(this);

			pComponent->OnInitialize();

			mComponents.Add(pComponent);
			return nullptr;
		}

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
					//TODO: destroy

					//_components.RemoveAt(i);
					return true;
				}
			}

			return false;
		}

		/// <summary>
		/// Destroys this entity
		/// </summary>
		void DestroyEntity();
	private:
		Entity(Scene* pScene);
		~Entity();
	private:
		Array<Component*> mComponents;
		Scene* mOwnerScene;
	};
}