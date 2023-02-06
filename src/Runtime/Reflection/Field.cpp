#include "Field.h"

namespace Portakal
{
	FieldDispatcher::FieldDispatcher(Field* pField, Type* ownerType)
	{
		ownerType->_RegisterField(pField);
	}
	FieldDispatcher::~FieldDispatcher()
	{

	}
	Field::Field(Type* pType, const String& name, const unsigned int offset) : mType(pType), mName(name), mOffset(offset)
	{

	}
}