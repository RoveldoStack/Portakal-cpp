#pragma once
#include <Runtime/Containers/String.h>
#include <Runtime/Reflection/Class.h>

namespace Portakal
{
	class Type;

	class PORTAKAL_API Attribute : public Class
	{
	public:
	};

	class PORTAKAL_API AttributeDispatcher
	{
	public:
		AttributeDispatcher(Attribute* pAttribute, Type* pType);
		~AttributeDispatcher() = default;
	};

#define GENERATE_ATTRIBUTE(target,attribute,...)\
	class EXPORT EMPTY(target)EMPTY(attribute) : public attribute\
	{\
		static attribute* GenerateAttribute()\
		{\
			attribute* pAttribute = new attribute(__VA_ARGS__);\
			AttributeDispatcher::AttributeDispatcher(pAttribute, typeof(target));\
			return (attribute*)pAttribute;\
		}\
		static inline Attribute* sAttribute = GenerateAttribute();\
	};
}