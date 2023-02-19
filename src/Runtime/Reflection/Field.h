#pragma once
#include <Runtime/Reflection/Type.h>
#include <Runtime/Reflection/AccessSpecifier.h>
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

		/// <summary>
		/// Sets the field value
		/// </summary>
		/// <typeparam name="TValue"></typeparam>
		/// <param name="pObject"></param>
		/// <param name="value"></param>
		template<typename TValue>
		void SetValue(void* pObject, const TValue& value) noexcept
		{
			unsigned char* pObjectByte = (unsigned char*)pObject + mOffset;

			*pObjectByte = value;
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