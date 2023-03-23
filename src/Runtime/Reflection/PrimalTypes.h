#pragma once
#include <Runtime/Reflection/Type.h>

namespace Portakal
{

#define GENERATE_PRIMAL_TYPE(type)\
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
		FORCEINLINE virtual String GetTypeName() const noexcept override { return "int"; }\
		FORCEINLINE virtual void* CreateDefaultHeapObject() const noexcept override { return new EMPTY(type)(); }\
	};\
	template<>\
	class TypeAccessor<EMPTY(type)>\
	{\
	public:\
		FORCEINLINE static Type* GetAccessorType() { return EMPTY(type)_Type::GetStaticType(); }\
	};

	GENERATE_PRIMAL_TYPE(int);
	GENERATE_PRIMAL_TYPE(String);

}
