#pragma once
#include <Runtime/Reflection/Reflection.h>

namespace Portakal
{
	/// <summary>
	/// Attribute for marking a processor class to target a resource type
	/// </summary>
	PCLASS();
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

#include "CustomAssetProcessorAttribute.reflect.h"
}