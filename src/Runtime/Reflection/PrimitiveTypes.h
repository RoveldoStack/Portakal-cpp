#pragma once
#include <Runtime/Reflection/Type.h>
#include <Runtime/Math/Color4.h>
#include <Runtime/Containers/Array.h>

namespace Portakal
{

#define GENERATE_PRIMITIVE_TYPE(type,typecode)\
	class PORTAKAL_API EMPTY(type)_Type : public Type\
	{\
	private:\
		static EMPTY(type)_Type* GenerateTypeData()\
		{\
			EMPTY(type)_Type* pType = new EMPTY(type)_Type();\
			Assembly::GetProcessAssembly()->RegisterType(pType);\
			return pType;\
		}\
		static inline Type* sType = (Type*)GenerateTypeData();\
	public:\
		FORCEINLINE static Type* GetStaticType() { return sType; }\
		FORCEINLINE virtual unsigned int GetSize() const noexcept override { return sizeof(EMPTY(type)); }\
		FORCEINLINE virtual String GetTypeName() const noexcept override { return #type; }\
		FORCEINLINE virtual void* CreateDefaultHeapObject() const noexcept override { return new EMPTY(type)(); }\
		FORCEINLINE virtual bool IsPrimitive() const noexcept override { return true;}\
		FORCEINLINE virtual TypeCodes GetTypeCode() const noexcept override { return typecode;}\
	};\
	template<>\
	class TypeAccessor<EMPTY(type)>\
	{\
	public:\
		FORCEINLINE static Type* GetAccessorType() { return EMPTY(type)_Type::GetStaticType(); }\
	};

#define GENERATE_PRIMITIVE_TYPE2(type,typecode)\
	class PORTAKAL_API EMPTY(type)_Type : public Type\
	{\
	private:\
		static EMPTY(type)_Type* GenerateTypeData()\
		{\
			EMPTY(type)_Type* pType = new EMPTY(type)_Type();\
			Assembly::GetProcessAssembly()->RegisterType(pType);\
			return pType;\
		}\
		static inline Type* sType = (Type*)GenerateTypeData();\
	public:\
		FORCEINLINE static Type* GetStaticType() { return sType; }\
		FORCEINLINE virtual unsigned int GetSize() const noexcept override { return 0; }\
		FORCEINLINE virtual String GetTypeName() const noexcept override { return #type; }\
		FORCEINLINE virtual void* CreateDefaultHeapObject() const noexcept override { return nullptr; }\
		FORCEINLINE virtual bool IsPrimitive() const noexcept override { return false;}\
		FORCEINLINE virtual TypeCodes GetTypeCode() const noexcept override { return typecode;}\
		FORCEINLINE virtual bool IsArray() const noexcept override { return true;}\
	};\
	template<>\
	class TypeAccessor<EMPTY(type<char>)>\
	{\
	public:\
		FORCEINLINE static Type* GetAccessorType() { return EMPTY(type)_Type::GetStaticType(); }\
	};

	GENERATE_PRIMITIVE_TYPE(char,TypeCodes::Char);
	GENERATE_PRIMITIVE_TYPE(Byte,TypeCodes::UChar);
	GENERATE_PRIMITIVE_TYPE(float,TypeCodes::Float);
	GENERATE_PRIMITIVE_TYPE(double,TypeCodes::Double);
	GENERATE_PRIMITIVE_TYPE(Long,TypeCodes::Long);
	GENERATE_PRIMITIVE_TYPE(ULong,TypeCodes::ULong);
	GENERATE_PRIMITIVE_TYPE(LongLong, TypeCodes::LongLong);
	GENERATE_PRIMITIVE_TYPE(ULongLong, TypeCodes::ULongLong);
	GENERATE_PRIMITIVE_TYPE(int, TypeCodes::Int);
	GENERATE_PRIMITIVE_TYPE(String, TypeCodes::String);
	GENERATE_PRIMITIVE_TYPE(UInt, TypeCodes::UInt);
	GENERATE_PRIMITIVE_TYPE2(Array, TypeCodes::Composed);
}
