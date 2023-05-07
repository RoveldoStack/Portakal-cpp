#pragma once
#include <Runtime/Reflection/Reflection.h>

namespace Portakal
{
	class PORTAKAL_API CustomResourceSerializerAttribute : public Attribute
	{
		GENERATE_CLASS(CustomResourceSerializerAttribute);
	public:
		CustomResourceSerializerAttribute(const String& resourceType) : mResourceType(resourceType) {}
		CustomResourceSerializerAttribute() = default;
		~CustomResourceSerializerAttribute() = default;

		FORCEINLINE String GetResourceType() const noexcept { return mResourceType; }
	private:
		String mResourceType;
	};

#include "CustomResourceSerializerAttribute.reflect.h"
}