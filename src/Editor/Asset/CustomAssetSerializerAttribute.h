#pragma once
#include <Runtime/Reflection/Reflection.h>

namespace Portakal
{
	class PORTAKAL_API CustomAssetSerializerAttribute : public Attribute
	{
		GENERATE_CLASS(CustomAssetSerializerAttribute);
	public:
		CustomAssetSerializerAttribute(const String& resourceType,const Array<String>& extensions) : mResourceType(resourceType), mExtensions(extensions) {}
		CustomAssetSerializerAttribute() = default;
		~CustomAssetSerializerAttribute() = default;
		FORCEINLINE String GetResourceType() const noexcept { return mResourceType; }
		FORCEINLINE Array<String> GetExtensions() const noexcept { return mExtensions; }
	private: 
		String mResourceType;
		Array<String> mExtensions;
	};

	START_GENERATE_TYPE(CustomAssetSerializerAttribute);
	START_TYPE_PROPERTIES(CustomAssetSerializerAttribute);
	END_TYPE_PROPERTIES;
	CONCRETE_TYPE(CustomAssetSerializerAttribute);
	END_GENERATE_TYPE(CustomAssetSerializerAttribute);

	
}