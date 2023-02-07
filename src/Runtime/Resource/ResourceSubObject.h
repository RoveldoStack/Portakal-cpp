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

}