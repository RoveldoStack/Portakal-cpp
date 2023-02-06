#pragma once
#include <Runtime/Reflection/Type.h>

namespace Portakal
{
	class PORTAKAL_API Field
	{
	public:
		FORCEINLINE Type* GetFieldType() const noexcept { return mType; }
		FORCEINLINE String GetFieldName() const noexcept { return mName; }
		FORCEINLINE unsigned int GetOffset() const noexcept { return mOffset; }

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

	protected:
		Field(Type* pType, const String& name, const unsigned int offset);
		~Field() = default;
	private:
		Type* mType;
		String mName;
		unsigned int mOffset;
	};

	class PORTAKAL_API FieldDispatcher
	{
	public:
		FieldDispatcher(Field* pField, Type* ownerType);
		~FieldDispatcher();
	};
}