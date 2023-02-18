#pragma once
#include <Runtime/Reflection/Reflection.h>

namespace Portakal
{
	class PORTAKAL_API CustomResourceSerializerAttribute : public Attribute
	{
		GENERATE_CLASS(CustomResourceSerializerAttribute);
	public:
		CustomResourceSerializerAttribute(const String& type);
		~CustomResourceSerializerAttribute() = default;

		FORCEINLINE String GetType() const noexcept { return mType; }
	private:
		String mType;
	};

	START_GENERATE_TYPE(CustomResourceSerializerAttribute);
	START_TYPE_PROPERTIES(CustomResourceSerializerAttribute);
	END_TYPE_PROPERTIES;
	HAS_DEFAULT_CONSTRUCTOR(CustomResourceSerializerAttribute);
	END_GENERATE_TYPE(CustomResourceSerializerAttribute);
}