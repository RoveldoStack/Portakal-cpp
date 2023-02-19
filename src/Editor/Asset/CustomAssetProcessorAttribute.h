#pragma once
#include <Runtime/Reflection/Reflection.h>

namespace Portakal
{
	/// <summary>
	/// Attribute for marking a processor class to target a resource type
	/// </summary>
	class PORTAKAL_API CustomAssetProcessorAttribute : public Attribute
	{
		GENERATE_CLASS(CustomAssetProcessorAttribute);
	public:
		CustomAssetProcessorAttribute(const String& resourceType) : mResourceType(resourceType) {}
		CustomAssetProcessorAttribute() = default;
		~CustomAssetProcessorAttribute() = default;

		/// <summary>
		/// Returns the target resource type
		/// </summary>
		/// <returns></returns>
		FORCEINLINE String GetResourceType() const noexcept { return mResourceType; }
	private:
		String mResourceType;
	};

	START_GENERATE_TYPE(CustomAssetProcessorAttribute);
	START_TYPE_PROPERTIES(CustomAssetProcessorAttribute);
	END_TYPE_PROPERTIES;
	HAS_DEFAULT_CONSTRUCTOR(CustomAssetProcessorAttribute);
	END_GENERATE_TYPE(CustomAssetProcessorAttribute);
}