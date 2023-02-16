#pragma once
#include <Runtime/Reflection/Reflection.h>

namespace Portakal
{
	class PORTAKAL_API CustomAssetSerializerAttribute : public Attribute
	{
		GENERATE_CLASS(CustomAssetSerializerAttribute);
	public:
		CustomAssetSerializerAttribute(const String& resourceType) : mResourceType(resourceType){}
		CustomAssetSerializerAttribute() = default;
		~CustomAssetSerializerAttribute() = default;
		FORCEINLINE String GetResourceType() const noexcept { return mResourceType; }
	private: 
		String mResourceType;
	};

	START_GENERATE_TYPE(CustomAssetSerializerAttribute);
	START_TYPE_PROPERTIES(CustomAssetSerializerAttribute);
	END_TYPE_PROPERTIES;
	CONCRETE_TYPE(CustomAssetSerializerAttribute);
	END_GENERATE_TYPE(CustomAssetSerializerAttribute);

	
}