#pragma once
#include <Runtime/Reflection/Type.h>
#include <Runtime/Reflection/AccessSpecifier.h>
#include <Runtime/Memory/ByteBlock.h>
namespace Portakal
{
	/// <summary>
	/// Represents a reflectable field inside a class
	/// </summary>
	class PORTAKAL_API Field
	{
	public:
		Field(Type* pType, const String& name, const unsigned int offset,const AccessSpecifier accessSpecifier);
		~Field() = default;

		/// <summary>
		/// Returns the field type
		/// </summary>
		/// <returns></returns>
		FORCEINLINE Type* GetFieldType() const noexcept { return mType; }

		/// <summary>
		/// Returns the field name
		/// </summary>
		/// <returns></returns>
		FORCEINLINE String GetFieldName() const noexcept { return mName; }

		/// <summary>
		/// Returns the field offset inside its class
		/// </summary>
		/// <returns></returns>
		FORCEINLINE unsigned int GetOffset() const noexcept { return mOffset; }

		/// <summary>
		/// Returns the field access specifieds
		/// </summary>
		/// <returns></returns>
		FORCEINLINE AccessSpecifier GetAccessSpecifier() const noexcept { return mAccessSpecifier; }

		void GetRawBytes(void* pObject,ByteBlock& blockOut) const;

		/// <summary>
		/// Sets the field value
		/// </summary>
		/// <typeparam name="TValue"></typeparam>
		/// <param name="pObject"></param>
		/// <param name="value"></param>
		template<typename TValue>
		void SetValue(void* pObject, const TValue& value) const noexcept
		{
			unsigned char* pObjectByte = (unsigned char*)pObject + mOffset;
			TValue* pV = (TValue*)pObjectByte;
			*pV = value;
		}

		/// <summary>
		/// Returns the field value
		/// </summary>
		/// <typeparam name="TValue"></typeparam>
		/// <param name="pObject"></param>
		/// <returns></returns>
		template<typename TValue>
		TValue GetValue(void* pObject) const noexcept
		{
			unsigned char* pObjectByte = (unsigned char*)pObject + mOffset;

			return *(TValue*)pObjectByte;
		}
		template<typename TAddress>
		TAddress* GetAddress(void* pObject) const noexcept
		{
			unsigned char* pObjectByte = (unsigned char*)pObject + mOffset;
			return (TAddress*)pObjectByte;
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

#define REGISTER_FIELD(cls,member,type,accessSpecifier) pType->_RegisterField(new Field(TypeAccessor<type>::GetAccessorType(),#member,offsetof(cls,member),accessSpecifier));

#define REGISTER_FIELD_SELF(cls,member,accessSpecifier) pType->_RegisterField(new Field(pType,#member,offsetof(cls,member),accessSpecifier));
#define FIELD()
}