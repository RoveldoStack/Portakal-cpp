#pragma once
#include <Runtime/Reflection/Type.h>

namespace Portakal
{
	class PORTAKAL_API Field
	{
	public:
		FORCEINLINE Type* GetFieldType() const noexcept { return _type; }
		FORCEINLINE String GetFieldName() const noexcept { return _name; }
		FORCEINLINE unsigned int GetOffset() const noexcept { return _offset; }

		template<typename TValue>
		void SetValue(void* pObject, const TValue& value) noexcept
		{
			unsigned char* pObjectByte = (unsigned char*)pObject + _offset;

			*pObjectByte = value;
		}
		template<typename TValue>
		TValue GetValue(void* pObject) const noexcept
		{
			unsigned char* pObjectByte = (unsigned char*)pObject + _offset;

			return *(TValue*)pObjectByte;
		}

	protected:
		Field(Type* pType, const String& name, const unsigned int offset);
		~Field() = default;
	private:
		Type* _type;
		String _name;
		unsigned int _offset;
	};

	class PORTAKAL_API FieldDispatcher
	{
	public:
		FieldDispatcher(Field* pField, Type* ownerType);
		~FieldDispatcher();
	};
}