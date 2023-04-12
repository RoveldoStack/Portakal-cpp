#pragma once
#include <Runtime/Core/Core.h>

namespace Portakal
{
#define IS_ENUM() FORCEINLINE virtual void bool IsEnum() const noexcept override { return true;}

#define ENUM()

#define REGISTER_ENUM(name,value) pType->_RegisterEnum(#name,value);

#define START_GENERATE_ENUM(type)\
class PORTAKAL_API EMPTY(type)_Type : public Type\
	{\
	private:\
		static EMPTY(type)_Type* GenerateTypeData()\
		{\
			EMPTY(type)_Type* pType = new EMPTY(type)_Type();\


#define END_GENERATE_ENUM(type)\
Assembly::GetProcessAssembly()->RegisterType(pType);\
			return pType;\
		}\
		static inline Type* sType = (Type*)GenerateTypeData();\
	public:\
		FORCEINLINE static Type* GetStaticType() { return sType; }\
		FORCEINLINE virtual unsigned int GetSize() const noexcept override { return sizeof(EMPTY(type)); }\
		FORCEINLINE virtual String GetTypeName() const noexcept override { return #type; }\
		FORCEINLINE virtual void* CreateDefaultHeapObject() const noexcept override { return new EMPTY(type)(); }\
		FORCEINLINE virtual bool IsEnum() const noexcept override { return true;}\
	};\
	template<>\
	class TypeAccessor<EMPTY(type)>\
	{\
	public:\
		FORCEINLINE static Type* GetAccessorType() { return EMPTY(type)_Type::GetStaticType(); }\
	};
}