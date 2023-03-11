#pragma once
#include <Runtime/World/SceneDescriptor.h>
#include <Runtime/World/SceneAspect.h>
#include <Runtime/Reflection/Reflection.h>
#include <Runtime/Object/TaggedObject.h>

namespace Portakal
{
	class SceneAspect;
	class Entity;

	/// <summary>
	/// Scene represents a collection of entities and aspects.
	/// Aspects defines the properties of a scene.
	/// Entities populates these properties.
	/// </summary>
	class PORTAKAL_API Scene : public TaggedObject
	{
		friend class SceneAPI;
	public:
		/// <summary>
		/// Returns the entities
		/// </summary>
		/// <returns></returns>
		Array<Entity*> GetEntities() const noexcept { return mEntities; }

		/// <summary>
		/// Returns the aspects
		/// </summary>
		/// <returns></returns>
		Array<SceneAspect*> GetAspects() const noexcept { return mAspects; }

		/// <summary>
		/// Returns whether its the primal scene
		/// </summary>
		/// <returns></returns>
		FORCEINLINE bool IsPrimal() const noexcept { return mPrimal; }

		/// <summary>
		/// Returns whether its currently active and running
		/// </summary>
		FORCEINLINE bool IsActive() const noexcept { return mActive; }

		/// <summary>
		/// Generates and outputs the descriptor of this scene
		/// </summary>
		/// <param name="outDescriptor"></param>
		void GenerateDescriptor(SceneDescriptor& outDescriptor) const noexcept;

		/// <summary>
		/// Creates anew entity
		/// </summary>
		/// <returns></returns>
		Entity* CreateEntity();

		/// <summary>
		/// Deletes the existing entity
		/// </summary>
		/// <param name="pEntity"></param>
		/// <returns></returns>
		bool DeleteEntity(Entity* pEntity);

		/// <summary>
		/// Creates anew aspect with the given template type
		/// </summary>
		/// <typeparam name="TComponent"></typeparam>
		template<typename TAspect,typename... TParameters>
		TAspect* CreateAspect(TParameters... parameters)
		{
			if (GetAspect<TAspect>() != nullptr)
				return nullptr;

			TAspect* pAspect = new TAspect(parameters...);

			pAspect->_SetOwnerScene(this);

			pAspect->OnInitialize();

			mAspects.Add(pAspect);

			return pAspect;
		}

		/// <summary>
		/// Creates anew aspect with the given type
		/// </summary>
		/// <param name="state"></param>
		SceneAspect* CreateAspect(const Type* pType)
		{
			if (GetAspect(pType) != nullptr)
				return nullptr;

			SceneAspect* pAspect = (SceneAspect*)pType->CreateDefaultHeapObject();

			if (pAspect == nullptr)
				return nullptr;

			pAspect->_SetOnwerScene(this);

			pAspect->OnInitialize();

			mAspects.Add(pAspect);

			return pAspect;
		}

		/// <summary>
		/// Deletes the aspect with the given type
		/// </summary>
		/// <param name="pType"></param>
		/// <returns></returns>
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

		/// <summary>
		/// Deletes the aspect with the given template type
		/// </summary>
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

		/// <summary>
		/// Returns the aspect with the given template type
		/// </summary>
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

		/// <summary>
		/// Returns the aspect with the given type
		/// </summary>
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

		/// <summary>
		/// Marks this scene as the primal scene
		/// </summary>
		void MarkPrimal();

		/// <summary>
		/// Activates the scene, this activation can be ignored by some scene aspects
		/// </summary>
		void SetActivationState(const bool bActive);

		virtual void DestroyCore() override;
	private:
		Scene(const SceneDescriptor& descriptor);
		Scene();

		void CreateFromDescriptor(const SceneDescriptor& descriptor);
		/// <summary>
		/// Internal primal state setter
		/// </summary>
		void _SetPrimalState(const bool state) { mPrimal = state; }

		/// <summary>
		/// Internal active state setter
		/// </summary>
		void _SetActiveState(const bool state) { mActive = state; }
	private:
		Array<SceneAspect*> mAspects;
		Array<Entity*> mEntities;
		bool mPrimal;
		bool mActive;
	};
}