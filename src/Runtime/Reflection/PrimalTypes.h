#pragma once
#include <Runtime/Reflection/Type.h>

namespace Portakal
{
	class PORTAKAL_API int_Type : public Type
	{
	private:
		static int_Type* GenerateTypeData()
		{
			int_Type* pType = new int_Type();
			Assembly::GetProcessAssembly()->RegisterType(pType);
			return pType;
		}
		static inline Type* sType = (Type*)GenerateTypeData();
	public:
		FORCEINLINE static Type* GetStaticType() { return sType; }
		FORCEINLINE virtual unsigned int GetSize() const noexcept override { return sizeof(int); }
		FORCEINLINE virtual String GetTypeName() const noexcept override { return "int"; }
		FORCEINLINE virtual void* CreateDefaultHeapObject() const noexcept override { return new int(); }
	};
	template<>
	class TypeAccessor<int>
	{
	public:
		FORCEINLINE static Type* GetAccessorType() { return int_Type::GetStaticType(); }
	};
}
