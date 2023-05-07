#pragma once
#include <Runtime/Reflection/Reflection.h>

namespace Portakal
{
	/// <summary>
	/// Attribute for a importer class to target a resource type
	/// </summary>
	PCLASS();
	class PORTAKAL_API CustomAssetImporterAttribute : public Attribute
	{
		GENERATE_CLASS(CustomAssetImporterAttribute);
	public:
		CustomAssetImporterAttribute(const String& resourceType,const Array<String>& extensions) : mResourceType(resourceType),mExtensions(extensions) {}
		CustomAssetImporterAttribute() = default;
		~CustomAssetImporterAttribute() = default;

		/// <summary>
		/// Returns the target resource type
		/// </summary>
		/// <returns></returns>
		FORCEINLINE String GetResourceType() const noexcept { return mResourceType; }

		/// <summary>
		/// Returns the target extensions for the resource type
		/// </summary>
		/// <returns></returns>
		FORCEINLINE Array<String> GetExtensions() const noexcept { return mExtensions; }
	private:
		String mResourceType;
		Array<String> mExtensions;
	};

#include "CustomAssetImporterAttribute.reflect.h"

}