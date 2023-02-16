#pragma once
#include <Runtime/Reflection/Reflection.h>

namespace Portakal
{
	class PORTAKAL_API CustomAssetProcessorAttribute : public Attribute
	{
		GENERATE_CLASS(CustomAssetProcessorAttribute);
	public:
		CustomAssetProcessorAttribute(const String& resourceType) : mResourceType(resourceType) {}
		CustomAssetProcessorAttribute() = default;
		~CustomAssetProcessorAttribute() = default;

		FORCEINLINE String GetResourceType() const noexcept { return mResourceType; }
	private:
		String mResourceType;
	};

	START_GENERATE_TYPE(CustomAssetProcessorAttribute);
	START_TYPE_PROPERTIES(CustomAssetProcessorAttribute);
	END_TYPE_PROPERTIES;
	CONCRETE_TYPE(CustomAssetProcessorAttribute);
	END_GENERATE_TYPE(CustomAssetProcessorAttribute);
}