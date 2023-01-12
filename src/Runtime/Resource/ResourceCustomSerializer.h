#pragma once
#include <Runtime/Reflection/Type.h>
#include <Runtime/Reflection/Attribute.h>

namespace Portakal
{
	class PORTAKAL_API ResourceCustomSerializer : Attribute
	{
		GENERATE_CLASS(ResourceCustomSerializer);
	public:
		ResourceCustomSerializer(Type* pType) { _customSerializer = pType; }
		ResourceCustomSerializer() { _customSerializer = nullptr}
		~ResourceCustomSerializer() = default;

		FORCEINLINE Type* GetCustomSerializer() const noexcept { return _customSerializer; }
	private:
		Type* _customSerializer;
	};

}