#pragma once
#include <Runtime/Reflection/Reflection.h>

namespace Portakal
{
	class PORTAKAL_API CustomAssetImporterAttribute : public Attribute
	{
		GENERATE_CLASS(CustomAssetImporterAttribute);
	public:
		CustomAssetImporterAttribute(const String& resourceType,const Array<String>& extensions) : mResourceType(resourceType),mExtensions(extensions) {}
		CustomAssetImporterAttribute() = default;
		~CustomAssetImporterAttribute() = default;

		FORCEINLINE String GetResourceType() const noexcept { return mResourceType; }
		FORCEINLINE Array<String> GetExtensions() const noexcept { return mExtensions; }
	private:
		String mResourceType;
		Array<String> mExtensions;
	};

	START_GENERATE_TYPE(CustomAssetImporterAttribute);
	START_TYPE_PROPERTIES(CustomAssetImporterAttribute);
	END_TYPE_PROPERTIES;
	HAS_DEFAULT_CONSTRUCTOR(CustomAssetImporterAttribute);
	END_GENERATE_TYPE(CustomAssetImporterAttribute);
}