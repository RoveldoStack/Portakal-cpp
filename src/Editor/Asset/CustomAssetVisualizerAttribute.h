#pragma once
#include <Runtime/Reflection/Reflection.h>

namespace Portakal
{
	class PORTAKAL_API CustomAssetVisualizerAttribute : public Attribute
	{
		GENERATE_CLASS(CustomAssetVisualizerAttribute);
	public:
		CustomAssetVisualizerAttribute(const String& resourceType) : mResourceType(resourceType) {}
		CustomAssetVisualizerAttribute() = default;
		~CustomAssetVisualizerAttribute() = default;
		FORCEINLINE String GetResourceType() const noexcept { return mResourceType; }
	private:
		String mResourceType;
	};

	START_GENERATE_TYPE(CustomAssetVisualizerAttribute);
	START_TYPE_PROPERTIES(CustomAssetVisualizerAttribute);
	END_TYPE_PROPERTIES;
	CONCRETE_TYPE(CustomAssetVisualizerAttribute);
	END_GENERATE_TYPE(CustomAssetVisualizerAttribute);
}