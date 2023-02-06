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
		friend class BaseTypeDispatcher;
	public:
		Type() = default;
		~Type() = default;

		FORCEINLINE Field* GetField(const String& name);
		FORCEINLINE Array<Field*> GetFields() const noexcept { return mFields; }
		FORCEINLINE Array<Type*> GetBaseTypes() const noexcept { return mBaseTypes; }
		FORCEINLINE bool IsSubClassOf(const Type* pType) const noexcept;

		template<typename TAttribute>
		TAttribute* GetAttribute() const noexcept
		{
			Type* pAttributeType = TypeAccessor<TAttribute>::GetAccessorType();

			for (unsigned int i = 0; i < mAttributes.GetCursor(); i++)
			{
				Attribute* pAttribute = mAttributes[i];

				if (pAttributeType == pAttribute->GetType())
					return (TAttribute*)pAttribute;
			}

			return nullptr;
		}
		FORCEINLINE virtual unsigned int GetSize() const noexcept = 0;
		FORCEINLINE virtual String GetTypeName() const noexcept = 0;
		FORCEINLINE virtual void* CreateDefaultHeapObject() const noexcept = 0;
	protected:
		void _RegisterBaseType(Type* pType);
		FORCEINLINE void _RegisterField(Field* pField);
		FORCEINLINE void _RegisterAttribute(Attribute* pAttribute);
	private:
		Array<Field*> mFields;
		Array<Attribute*> mAttributes;
		Array<Type*> mBaseTypes;
	};

	template<typename TType>
	class TypeAccessor
	{

	};

	class PORTAKAL_API BaseTypeDispatcher
	{
	public:
		BaseTypeDispatcher(Type* pTargetType, Type* pBaseType);
		~BaseTypeDispatcher() = default;
	};

#define START_GENERATE_TYPE(type) class PORTAKAL_API EMPTY(type)_Type : public Type\
									{\
									private:


#define START_TYPE_PROPERTIES(type) static EMPTY(type)_Type* GenerateTypeData() { EMPTY(type)_Type* pType = new EMPTY(type)_Type; type::SetType(pType); Assembly::GetProcessAssembly()->RegisterType(pType); 

#define END_TYPE_PROPERTIES  return pType; } static inline Type* sType = (Type*)GenerateTypeData(); public:

#define END_GENERATE_TYPE(type)			FORCEINLINE static Type* GetStaticType() { return sType; }\
										FORCEINLINE virtual unsigned int GetSize() const noexcept override { return sizeof(type); }\
										FORCEINLINE virtual String GetTypeName() const noexcept override { return #type; }\
									 };\
									 template<>\
									 class TypeAccessor<type>\
									 {\
									 public:\
										 FORCEINLINE static Type* GetAccessorType() { return EMPTY(type)_Type::GetStaticType(); }\
									 };

#define REGISTER_BASE_TYPE(baseType) pType->_RegisterBaseType(typeof(baseType)); 

#define EMPTY(name) name



#define VIRTUAL_TYPE FORCEINLINE virtual void* CreateDefaultHeapObject() const noexcept override { return nullptr; }

#define CONCRETE_TYPE(type) FORCEINLINE virtual void* CreateDefaultHeapObject() const noexcept override { return new type(); }

#define typeof(type) TypeAccessor<type>::GetAccessorType()
}