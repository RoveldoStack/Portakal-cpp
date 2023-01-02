#pragma once
#include <Runtime/Object/TaggedObject.h>
#include <Runtime/World/Component.h>
#include <Runtime/Containers/Array.h>

namespace Portakal
{
	class Scene;
	class PORTAKAL_API Entity : public TaggedObject
	{
	public:
		FORCEINLINE Scene* GetOwnerScene() const noexcept { return _ownerScene; }
		FORCEINLINE Array<Component*> GetComponents() const noexcept { return _components; }

		Component* CreateComponent(Type* pType)
		{
			Component* pComponent = (Component*)pType->CreateDefaultHeapObject();
			if (pComponent == nullptr)
				return nullptr;

			pComponent->_SetOwnerEntity(this);

			pComponent->OnInitialize();

			_components.Add(pComponent);
			return nullptr;
		}

		template<typename TComponent,typename... TParameters>
		TComponent* CreateComponent(TParameters... parameters)
		{
			TComponent* pComponent = new TComponent(parameters...);

			pComponent->_SetOwnerEntity(this);

			pComponent->OnInitialize();

			_components->Add(pComponent);

			return pComponent;
		}

		template<typename TComponent>
		TComponent* GetComponent() const
		{
			Type* pType = TypeAccessor<TComponent>::GetAccessorType();

			for (unsigned int i = 0; i < _components.GetCursor(); i++)
			{
				Component* pComponent = _components[i];
				if (pComponent->GetType() == pType)
					return (TComponent*)pComponent;
			}

			return nullptr;
		}


		template<typename TComponent>
		bool HasComponent() const
		{
			Type* pType = TypeAccessor<TComponent>::GetAccessorType();

			for (unsigned int i = 0; i < _components.GetCursor(); i++)
			{
				Component* pComponent = _components[i];
				if (pComponent->GetType() == pType)
					return true;
			}

			return false;
		}

		bool HasComponent(const Type* pType)
		{
			for (unsigned int i = 0; i < _components.GetCursor(); i++)
			{
				Component* pComponent = _components[i];
				if (pComponent->GetType() == pType)
					return true;
			}
			return false;
		}

		template<typename TComponent>
		bool DeleteComponent()
		{
			const Type* pType = TypeAccessor<TComponent>::GetAccessorType();
			for (unsigned int i = 0; i < _components.GetCursor(); i++)
			{
				Component* pComponent = _components[i];

				if (pComponent->GetType() == pType)
				{
					//TODO: destroy

					//_components.RemoveAt(i);
					return true;
				}
			}

			return false;
		}

		void DestroyEntity();
	private:
		Array<Component*> _components;
		Scene* _ownerScene;
	};
}