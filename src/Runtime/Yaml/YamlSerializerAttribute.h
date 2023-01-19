#pragma once
#include <Runtime/Reflection/Reflection.h>

namespace Portakal
{
	class PORTAKAL_API YamlSerializerAttribute : public Attribute
	{
		GENERATE_CLASS(YamlSerializerAttribute);
	public:
		YamlSerializerAttribute(Type* pTarget) : _targetSerializerType(pTarget) {}
		YamlSerializerAttribute() : _targetSerializerType(nullptr) {}
		~YamlSerializerAttribute() = default;

		FORCEINLINE Type* GetTargetSerializerType() const noexcept { return _targetSerializerType; }
	private:
		Type* _targetSerializerType;
	};


	START_GENERATE_TYPE(YamlSerializerAttribute);
	START_TYPE_PROPERTIES(YamlSerializerAttribute);
	END_TYPE_PROPERTIES;
	CONCRETE_TYPE(YamlSerializerAttribute);
	END_GENERATE_TYPE(YamlSerializerAttribute);
}