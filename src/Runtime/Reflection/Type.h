#pragma once
#include <Runtime/Containers/Array.h>
#include <Runtime/Containers/String.h>
#include <Runtime/Reflection/Assembly.h>
#include <Runtime/Reflection/Attribute.h>

namespace Portakal
{
	class Field;

	class PORTAKAL_API Type
	{
		friend class FieldDispatcher;
		friend class AttributeDispatcher;
	public:
		Type() = default;
		~Type() = default;

		FORCEINLINE Field* GetField(const String& name);
		FORCEINLINE Array<Field*> GetFields() const noexcept { return _fields; }
		FORCEINLINE Array<Type*> GetBaseTypes() const noexcept { return _baseTypes; }
		FORCEINLINE bool IsSubClassOf(const Type* pType) const noexcept;

		FORCEINLINE virtual unsigned int GetSize() const noexcept = 0;
		FORCEINLINE virtual String GetTypeName() const noexcept = 0;
		FORCEINLINE virtual void* CreateDefaultHeapObject() const noexcept = 0;
	protected:
		void RegisterBaseType(Type* pType);
	private:
		FORCEINLINE void _RegisterField(Field* pField);
		FORCEINLINE void _RegisterAttribute(Attribute* pAttribute);
	private:
		Array<Field*> _fields;
		Array<Attribute*> _attributes;
		Array<Type*> _baseTypes;
	};

	template<typename TType>
	class TypeAccessor
	{

	};

#define EMPTY(name) name
#define GENERATE_TYPE(type)			class PORTAKAL_API EMPTY(type)_Type : public Type\
									{\
									private:\
										static EMPTY(type)_Type* GenerateTypeData() { EMPTY(type)_Type* pType = new EMPTY(type)_Type; type::SetType(pType); Assembly::GetProcessAssembly()->RegisterType(pType); return pType; }\
										static inline Type* sType = (Type*)GenerateTypeData();\
									public:\
										FORCEINLINE static Type* GetStaticType() { return sType; }\
										FORCEINLINE virtual unsigned int GetSize() const noexcept override { return sizeof(type); }\
										FORCEINLINE virtual String GetTypeName() const noexcept override { return #type; }\
										FORCEINLINE virtual void* CreateDefaultHeapObject() const noexcept override { return new type(); }\
									 };\
									 template<>\
									 class TypeAccessor<type>\
									 {\
									 public:\
										 FORCEINLINE static Type* GetAccessorType() { return EMPTY(type)_Type::GetStaticType(); }\
									 };\

#define GENERATE_VIRTUAL_TYPE(type)	class PORTAKAL_API EMPTY(type)_Type : public Type\
									{\
									private:\
										static EMPTY(type)_Type* GenerateTypeData() { EMPTY(type)_Type* pType = new EMPTY(type)_Type(); type::SetType(pType); Assembly::GetProcessAssembly()->RegisterType(pType); return pType; }\
										static inline Type* sType = (Type*)GenerateTypeData();\
									public:\
										FORCEINLINE static Type* GetStaticType() { return sType; }\
										FORCEINLINE virtual unsigned int GetSize() const noexcept override { return sizeof(type); }\
										FORCEINLINE virtual String GetTypeName() const noexcept override { return #type; }\
										FORCEINLINE virtual void* CreateDefaultHeapObject() const noexcept override { return nullptr; }\
									 };\
									 template<>\
									 class TypeAccessor<type>\
									 {\
									 public:\
										 FORCEINLINE static Type* GetAccessorType() { return EMPTY(type)_Type::GetStaticType(); }\
									 };\


#define GENERATE_TYPELESS(type) class PORTAKAL_API EMPTY(type)_Type : public Type\
									{\
									private:\
										static EMPTY(type)_Type* GenerateTypeData() { return new EMPTY(type)_Type(); }\
										static inline Type* sType = (Type*)GenerateTypeData();\
									public:\
										FORCEINLINE static Type* GetStaticType() { return sType; }\
										FORCEINLINE virtual unsigned int GetSize() const noexcept override { return 0; }\
										FORCEINLINE virtual String GetTypeName() const noexcept override { return #type; }\
										FORCEINLINE virtual void* CreateDefaultHeapObject() const noexcept override { return nullptr; }\
									 };\
									 template<>\
									 class TypeAccessor<type>\
									 {\
									 public:\
										 FORCEINLINE static Type* GetAccessorType() { return EMPTY(type)_Type::GetStaticType(); }\
									 };\

#define REGISTER_BASE_TYPE(targetType,baseType)

#define typeof(type) TypeAccessor<type>::GetAccessorType()
}