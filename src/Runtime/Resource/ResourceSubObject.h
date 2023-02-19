#pragma once
#include <Runtime/Object/TaggedObject.h>

namespace Portakal
{
	class Resource;

	/// <summary>
	/// Represents a loaded resource object
	/// </summary>
	class PORTAKAL_API ResourceSubObject : public TaggedObject
	{
		GENERATE_CLASS(ResourceSubObject);
	public:

		/// <summary>
		/// Returns the resource owner 
		/// </summary>
		/// <returns></returns>
		FORCEINLINE Resource* GetOwnerResource() const noexcept { return mOwnerResource; }

		/// <summary>
		/// Returns whether it's a runtime generated resource. Package generated resources are not considered as a virtual resource!
		/// </summary>
		/// <returns></returns>
		FORCEINLINE bool IsVirtual() const noexcept{ return mOwnerResource == nullptr; }
	private:
		Resource* mOwnerResource;
	};

	START_GENERATE_TYPE(ResourceSubObject);
	START_TYPE_PROPERTIES(ResourceSubObject);
	REGISTER_BASE_TYPE(TaggedObject);
	END_TYPE_PROPERTIES;
	NO_DEFAULT_CONSTRUCTOR;
	END_GENERATE_TYPE(ResourceSubObject);

}