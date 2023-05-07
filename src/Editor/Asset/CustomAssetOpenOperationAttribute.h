#pragma once
#include <Runtime/Reflection/Reflection.h>

namespace Portakal
{
	PCLASS();
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
#include "CustomAssetOpenOperationAttribute.reflect.h"
}