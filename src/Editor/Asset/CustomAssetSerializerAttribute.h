#pragma once
#include <Runtime/Reflection/Reflection.h>

namespace Portakal
{
	/// <summary>
	/// Attribute for marking a serializer class to target a resource type
	/// </summary>
	PCLASS();
	class PORTAKAL_API CustomAssetSerializerAttribute : public Attribute
	{
		GENERATE_CLASS(CustomAssetSerializerAttribute);
	public:
		CustomAssetSerializerAttribute(const String& resourceType) : mResourceType(resourceType){}
		CustomAssetSerializerAttribute() = default;
		~CustomAssetSerializerAttribute() = default;

		/// <summary>
		/// Returns the resource type
		/// </summary>
		/// <returns></returns>
		FORCEINLINE String GetResourceType() const noexcept { return mResourceType; }
	private: 
		String mResourceType;
	};


#include "CustomAssetSerializerAttribute.reflect.h"

	
}