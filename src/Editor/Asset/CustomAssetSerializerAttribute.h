#pragma once
#include <Runtime/Reflection/Reflection.h>

namespace Portakal
{
	/// <summary>
	/// Attribute for marking a serializer class to target a resource type
	/// </summary>
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

	START_GENERATE_TYPE(CustomAssetSerializerAttribute);
	START_TYPE_PROPERTIES(CustomAssetSerializerAttribute);
	END_TYPE_PROPERTIES;
	HAS_DEFAULT_CONSTRUCTOR(CustomAssetSerializerAttribute);
	END_GENERATE_TYPE(CustomAssetSerializerAttribute);

	
}