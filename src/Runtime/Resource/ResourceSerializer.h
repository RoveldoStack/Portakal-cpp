#pragma once
#include <Runtime/Reflection/Reflection.h>

namespace Portakal
{
	class PORTAKAL_API ResourceSerializer : public Class
	{
		GENERATE_CLASS(ResourceSerializer);
	public:
		ResourceSerializer() = default;
		~ResourceSerializer() = default;

		virtual void Serialize() = 0;
		virtual void DeserializeFromRaw() = 0;
		virtual void DeserializeFromPackage() = 0;
	};
}