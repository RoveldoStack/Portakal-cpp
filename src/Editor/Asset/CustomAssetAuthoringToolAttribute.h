#pragma once
#include <Runtime/Reflection/Reflection.h>


namespace Portakal
{
	PCLASS();
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


#include "CustomAssetAuthoringToolAttribute.reflect.h"
}