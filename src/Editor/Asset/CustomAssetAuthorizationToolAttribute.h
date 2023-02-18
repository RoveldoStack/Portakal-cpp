#pragma once
#include <Runtime/Reflection/Reflection.h>


namespace Portakal
{
	class PORTAKAL_API CustomAssetAuthorizationToolAttribute : public Attribute
	{
		GENERATE_CLASS(CustomAssetAuthorizationToolAttribute);
	public:
		CustomAssetAuthorizationToolAttribute(const String& resourceType) : mResourceType(resourceType) {}
		CustomAssetAuthorizationToolAttribute() = default;
		~CustomAssetAuthorizationToolAttribute() = default;

		FORCEINLINE String GetResourceType() const noexcept { return mResourceType; }
	private:
		const String mResourceType;
	};

	START_GENERATE_TYPE(CustomAssetAuthorizationToolAttribute);
	START_TYPE_PROPERTIES(CustomAssetAuthorizationToolAttribute);
	END_TYPE_PROPERTIES;
	HAS_DEFAULT_CONSTRUCTOR(CustomAssetAuthorizationToolAttribute);
	END_GENERATE_TYPE(CustomAssetAuthorizationToolAttribute);
}