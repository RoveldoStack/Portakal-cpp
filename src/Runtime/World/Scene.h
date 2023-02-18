#pragma once
#include <Runtime/World/SceneDescriptor.h>
#include <Runtime/World/SceneAspect.h>
#include <Runtime/Reflection/Reflection.h>
#include <Runtime/Object/TaggedObject.h>

namespace Portakal
{
	class SceneAspect;
	class Entity;

	class PORTAKAL_API Scene : public TaggedObject
	{
		friend class SceneAPI;
	public:
		Array<Entity*> GetEntities() const noexcept { return mEntities; }
		Array<SceneAspect*> GetAspects() const noexcept { return mAspects; }
		FORCEINLINE bool IsPrimal() const noexcept { return mPrimal; }
		FORCEINLINE bool IsActive() const noexcept { return mActive; }

		Entity* CreateEntity();
		bool DeleteEntity(Entity* pEntity);

		template<typename TAspect,typename... TParameters>
		TAspect* CreateAspect(TParameters... parameters)
		{
			TAspect* pAspect = new TAspect(parameters...);

			pAspect->_SetOwnerScene(this);

			pAspect->OnInitialize();

			mAspects.Add(pAspect);

			return pAspect;
		}

		SceneAspect* CreateAspect(const Type* pType)
		{
			SceneAspect* pAspect = (SceneAspect*)pType->CreateDefaultHeapObject();

			if (pAspect == nullptr)
				return nullptr;

			pAspect->_SetOnwerScene(this);

			pAspect->OnInitialize();

			mAspects.Add(pAspect);

			return pAspect;
		}

		bool DeleteAspect(const Type* pType)
		{
			SceneAspect* pAspect = GetAspect(pType);

			if (pAspect == nullptr)
				return false;

			pAspect->OnFinalize();
			pAspect->_SetOnwerScene(nullptr);

			mAspects.Remove(pAspect);

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

			mAspects.Remove(pAspect);

			return true;
		}

		template<typename TComponent>
		TComponent* GetAspect()
		{
			const Type* pType = TypeAccessor<TComponent>::GetAccessorType();

			for (unsigned int i = 0; i < mAspects.GetCursor(); i++)
			{
				SceneAspect* pAspect = mAspects[i];
				if (pAspect->GetType() == pType)
					return (TComponent*)pAspect;
			}
			return nullptr;
		}

		SceneAspect* GetAspect(const Type* pType)
		{
			for (unsigned int i = 0; i < mAspects.GetCursor(); i++)
			{
				SceneAspect* pAspect = mAspects[i];
				if (pAspect->GetType() == pType)
					return pAspect;
			}
			return nullptr;
		}

		void MarkPrimal();
	private:
		Scene(const SceneDescriptor& descriptor);
		Scene();

		void _SetPrimalState(const bool state) { mPrimal = state; }
		void _SetActiveState(const bool state) { mActive = state; }
	private:
		Array<SceneAspect*> mAspects;
		Array<Entity*> mEntities;
		bool mPrimal;
		bool mActive;
	};
}