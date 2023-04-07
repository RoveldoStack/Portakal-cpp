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
		/// Destroys this component
		/// </summary>
		void DestroyComponent();

		/// <summary>
		/// Called upon first initialization
		/// </summary>
		virtual void OnInitialize() = 0;

		/// <summary>
		/// Called upon deletion
		/// </summary>
		virtual void OnFinalize() = 0;

	protected:
		Component() = default;
		~Component() = default;

		/// <summary>
		/// Internal setter for the owner entity
		/// </summary>
		/// <param name="pEntity"></param>
		void _SetOwnerEntity(Entity* pEntity) { mOwnerEntity = pEntity; }
	private:
		Entity* mOwnerEntity;
	};

	//START_GENERATE_TYPE(Component);
	//START_TYPE_PROPERTIES(Component);
	//REGISTER_BASE_TYPE(TaggedObject);
	//END_TYPE_PROPERTIES;
	//NO_DEFAULT_CONSTRUCTOR;
	//END_GENERATE_TYPE(Component);

#include "Component.reflect.h"
}