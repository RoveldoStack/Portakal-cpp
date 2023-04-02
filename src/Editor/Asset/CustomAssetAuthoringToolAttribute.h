#pragma once
#include <Runtime/Reflection/Reflection.h>


namespace Portakal
{
	class PORTAKAL_API CustomAssetAuthoringToolAttribute : public Attribute
	{
		GENERATE_CLASS(CustomAssetAuthoringToolAttribute);
	public:
		CustomAssetAuthoringToolAttribute(const String& resourceType) : mResourceType(resourceType) {}
		CustomAssetAuthoringToolAttribute() = default;
		~CustomAssetAuthoringToolAttribute() = default;

		FORCEINLINE String GetResourceType() const noexcept { return mResourceType; }
	private:
		const String mResourceType;
	};

	START_GENERATE_TYPE(CustomAssetAuthoringToolAttribute);
	START_TYPE_PROPERTIES(CustomAssetAuthoringToolAttribute);
	END_TYPE_PROPERTIES;
	HAS_DEFAULT_CONSTRUCTOR(CustomAssetAuthoringToolAttribute);
	END_GENERATE_TYPE(CustomAssetAuthoringToolAttribute);
}