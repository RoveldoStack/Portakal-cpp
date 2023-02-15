#pragma once
#include <Runtime/Reflection/Type.h>
#include <Runtime/Reflection/AccessSpecifier.h>
namespace Portakal
{
	class PORTAKAL_API Field
	{
	public:
		Field(Type* pType, const String& name, const unsigned int offset,const AccessSpecifier accessSpecifier);
		~Field() = default;

		FORCEINLINE Type* GetFieldType() const noexcept { return mType; }
		FORCEINLINE String GetFieldName() const noexcept { return mName; }
		FORCEINLINE unsigned int GetOffset() const noexcept { return mOffset; }
		FORCEINLINE AccessSpecifier GetAccessSpecifier() const noexcept { return mAccessSpecifier; }

		template<typename TValue>
		void SetValue(void* pObject, const TValue& value) noexcept
		{
			unsigned char* pObjectByte = (unsigned char*)pObject + mOffset;

			*pObjectByte = value;
		}
		template<typename TValue>
		TValue GetValue(void* pObject) const noexcept
		{
			unsigned char* pObjectByte = (unsigned char*)pObject + mOffset;

			return *(TValue*)pObjectByte;
		}
	private:
		Type* mType;
		String mName;
		unsigned int mOffset;
		AccessSpecifier mAccessSpecifier;
	};

	class PORTAKAL_API FieldDispatcher
	{
	public:
		FieldDispatcher(Field* pField, Type* ownerType);
		~FieldDispatcher();
	};

#define REGISTER_FIELD(member,type,accessSpecifier) pType->_RegisterField(new Field(typeof(type),#member,offsetof(type,name),acessSpecifier));
}