#pragma once
#include <Runtime/World/SceneDescriptor.h>
#include <Runtime/World/SceneAspect.h>
#include <Runtime/Reflection/Reflection.h>

namespace Portakal
{
	class SceneAspect;
	class Entity;

	class PORTAKAL_API Scene
	{
		friend class SceneAPI;
	public:
		FORCEINLINE bool IsPrimal() const noexcept { return _primal; }
		FORCEINLINE bool IsActive() const noexcept { return _active; }

		Entity* CreateEntity();
		bool deleteEntity(Entity* pEntity);

		template<typename TAspect,typename... TParameters>
		TAspect* CreateAspect(TParameters... parameters)
		{
			TAspect* pAspect = new TAspect(parameters...);

			pAspect->_SetOwnerScene(this);

			pAspect->OnInitialize();

			_aspects.Add(pAspect);

			return pAspect;
		}

		SceneAspect* CreateAspect(const Type* pType)
		{
			SceneAspect* pAspect = (SceneAspect*)pType->CreateDefaultHeapObject();

			if (pAspect == nullptr)
				return nullptr;

			pAspect->_SetOnwerScene(this);

			pAspect->OnInitialize();

			_aspects.Add(pAspect);

			return pAspect;
		}

		bool DeleteAspect(const Type* pType)
		{
			SceneAspect* pAspect = GetAspect(pType);

			if (pAspect == nullptr)
				return false;

			pAspect->OnFinalize();
			pAspect->_SetOnwerScene(nullptr);

			_aspects.Remove(pAspect);

			return true;
		}

		template<typename TAspect>
		bool DeleteAspect()
		{
			SceneAspect* pAspect = GetAspect<TAspect>();
			if (pAspect == nullptr)
				return false;

			pAspect->OnFinalize();
			pAspect->_SetOnwerScene(nullptr);

			_aspects.Remove(pAspect);

			return true;
		}

		template<typename TComponent>
		TComponent* GetAspect()
		{
			const Type* pType = TypeAccessor<TComponent>::GetAccessorType();

			for (unsigned int i = 0; i < _aspects.GetCursor(); i++)
			{
				SceneAspect* pAspect = _aspects[i];
				if (pAspect->GetType() == pType)
					return (TComponent*)pAspect;
			}
			return nullptr;
		}

		SceneAspect* GetAspect(const Type* pType)
		{
			for (unsigned int i = 0; i < _aspects.GetCursor(); i++)
			{
				SceneAspect* pAspect = _aspects[i];
				if (pAspect->GetType() == pType)
					return pAspect;
			}
			return nullptr;
		}

	private:
		Scene(const SceneDescriptor& descriptor);
		Scene();

		void _SetPrimalState(const bool state) { _primal = state; }
		void _SetActiveState(const bool state) { _active = state; }
	private:
		Array<SceneAspect*> _aspects;
		Array<Entity*> _entities;
		bool _primal;
		bool _active;
	};
}