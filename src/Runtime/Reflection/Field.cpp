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
	Field::Field(Type* pType, const String& name, const unsigned int offset,const AccessSpecifier accessSpecifier) : mType(pType), mName(name), mOffset(offset),mAccessSpecifier(accessSpecifier)
	{

	}
	void Field::GetRawBytes(void* pObject, ByteBlock& blockOut) const
	{
		unsigned char* pData = (unsigned char*)pObject;
		blockOut.Copy(pData, GetFieldType()->GetSize());
	}
}