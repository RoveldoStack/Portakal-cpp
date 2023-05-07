#pragma once
#include <Runtime/Reflection/Reflection.h>

namespace Portakal
{
	/// <summary>
	/// Used for marking serializer class and enabling him to be viewed by the reflection, so can yaml framework can find it and use it for the target type
	/// </summary>
	PCLASS();
	class PORTAKAL_API YamlSerializerAttribute : public Attribute
	{
		GENERATE_CLASS(YamlSerializerAttribute);
	public:
		YamlSerializerAttribute(Type* pTarget) : _targetSerializerType(pTarget) {}
		YamlSerializerAttribute() : _targetSerializerType(nullptr) {}
		~YamlSerializerAttribute() = default;

		/// <summary>
		/// Returns the target serializer type
		/// </summary>
		/// <returns></returns>
		FORCEINLINE Type* GetTargetSerializerType() const noexcept { return _targetSerializerType; }
	private:
		Type* _targetSerializerType;
	};

#include "YamlSerializerAttribute.reflect.h"
}