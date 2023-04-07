#pragma once
#include <Runtime/Reflection/Reflection.h>

namespace Portakal
{
	class PORTAKAL_API CustomAssetOpenOperationAttribute : public Attribute
	{
		GENERATE_CLASS(CustomAssetOpenOperationAttribute);
	public:
		CustomAssetOpenOperationAttribute(const String& pType) : mResourceType(pType) {}
		CustomAssetOpenOperationAttribute() : mResourceType(nullptr) {}
		~CustomAssetOpenOperationAttribute() = default;

		FORCEINLINE String GetResourceType() const noexcept { return mResourceType; }
	private:
		String mResourceType;
	};
	//START_GENERATE_TYPE(CustomAssetOpenOperationAttribute);
	//START_TYPE_PROPERTIES(CustomAssetOpenOperationAttribute);
	//END_TYPE_PROPERTIES;
	//HAS_DEFAULT_CONSTRUCTOR(CustomAssetOpenOperationAttribute);
	//END_GENERATE_TYPE(CustomAssetOpenOperationAttribute);


#include "CustomAssetOpenOperationAttribute.reflect.h"
}