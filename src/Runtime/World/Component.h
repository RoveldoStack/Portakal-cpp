#pragma once
#include <Runtime/Object/TaggedObject.h>

namespace Portakal
{
	class Entity;

	/// <summary>
	/// A component is a sub object of a scene entity, component may hold data,logic or both
	/// </summary>
	class PORTAKAL_API Component : public TaggedObject
	{
		GENERATE_CLASS(Component,Virtual);
		friend class Entity;
	public:
		/// <summary>
		/// Returns the owner entity of this component
		/// </summary>
		/// <returns></returns>
		FORCEINLINE Entity* GetOwnerEntity() const noexcept { return mOwnerEntity; }

		/// <summary>
		/// Called upon first initialization
		/// </summary>
		virtual void OnInitialize() = 0;

		/// <summary>
		/// Called upon deletion
		/// </summary>
		virtual void OnFinalize() = 0;

	protected:
		Component() : mOwnerEntity(nullptr){}
		~Component() = default;

		/// <summary>
		/// Internal setter for the owner entity
		/// </summary>
		/// <param name="pEntity"></param>
		void _SetOwnerEntity(Entity* pEntity) { mOwnerEntity = pEntity; }
	private:
		virtual void DestroyCore() override;
	private:
		Entity* mOwnerEntity;
	};

#include "Component.reflect.h"
}