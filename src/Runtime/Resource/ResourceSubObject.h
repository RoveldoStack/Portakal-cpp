#pragma once
#include <Runtime/Object/TaggedObject.h>

namespace Portakal
{
	class Resource;
	class PORTAKAL_API ResourceSubObject : public TaggedObject
	{
		GENERATE_CLASS(ResourceSubObject);
	public:
		FORCEINLINE Resource* GetOwnerResource() const noexcept { return mOwnerResource; }
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