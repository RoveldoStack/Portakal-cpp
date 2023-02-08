#pragma once
#include <Runtime/Reflection/Reflection.h>

namespace Portakal
{
	class PORTAKAL_API CustomAssetSerializerAttribute : public Attribute
	{
		GENERATE_CLASS(CustomAssetSerializerAttribute);
	public:
		CustomAssetSerializerAttribute(const String& type,const Array<String>& extensions) : mType(type), mExtensions(extensions) {}
		CustomAssetSerializerAttribute() = default;
		~CustomAssetSerializerAttribute() = default;
		FORCEINLINE String GetTypeName() const noexcept { return mType; }
		FORCEINLINE Array<String> GetExtensions() const noexcept { return mExtensions; }
	private: 
		String mType;
		Array<String> mExtensions;
	};

	START_GENERATE_TYPE(CustomAssetSerializerAttribute);
	START_TYPE_PROPERTIES(CustomAssetSerializerAttribute);
	END_TYPE_PROPERTIES;
	CONCRETE_TYPE(CustomAssetSerializerAttribute);
	END_GENERATE_TYPE(CustomAssetSerializerAttribute);

	
}