#pragma once
#include <Runtime/Reflection/Reflection.h>

namespace Portakal
{
	/// <summary>
	/// Attribute for marking a visualizer class to target a resource type
	/// </summary>,
	PCLASS();
	class PORTAKAL_API CustomAssetVisualizerAttribute : public Attribute
	{
		GENERATE_CLASS(CustomAssetVisualizerAttribute);
	public:
		CustomAssetVisualizerAttribute(const String& resourceType) : mResourceType(resourceType) {}
		CustomAssetVisualizerAttribute() = default;
		~CustomAssetVisualizerAttribute() = default;

		/// <summary>
		/// Returns the target resource type
		/// </summary>
		/// <returns></returns>
		FORCEINLINE String GetResourceType() const noexcept { return mResourceType; }
	private:
		String mResourceType;
	};


#include "CustomAssetVisualizerAttribute.reflect.h"
}