#pragma once
#include <Runtime/Containers/String.h>
#include <Runtime/Reflection/Class.h>

namespace Portakal
{
	class Type;

	class PORTAKAL_API Attribute : public Class
	{
	public:
		Attribute() = default;
		~Attribute() = default;
	};

	class PORTAKAL_API AttributeDispatcher
	{
	public:
		AttributeDispatcher(Attribute* pAttribute, Type* pType);
		~AttributeDispatcher() = default;
	};

#define REGISTER_TYPE_ATTRIBUTE(attribute,...) pType->_RegisterAttribute(new attribute(__VA_ARGS__));
}