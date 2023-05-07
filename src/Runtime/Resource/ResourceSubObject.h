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
		friend class Resource;
		GENERATE_CLASS(ResourceSubObject,Virtual);
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
		void _SetOwnerResource(Resource* pOwnerResource) { mOwnerResource = pOwnerResource; }
	private:
		Resource* mOwnerResource;
	};

#include "ResourceSubObject.reflect.h"

}