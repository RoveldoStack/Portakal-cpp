#pragma once
#include <Runtime/Containers/Array.h>
#include <Runtime/Containers/String.h>
#include <Runtime/Reflection/Assembly.h>
#include <Runtime/Reflection/Attribute.h>
#include <Runtime/Reflection/AccessSpecifier.h>
#include <Runtime/Reflection/TypeCodes.h>

namespace Portakal
{
	class Field;

	/// <summary>
	/// Utility type accessor class for enabling to access the type information outside of the class
	/// </summary>
	/// <typeparam name="TType"></typeparam>
	template<typename TType>
	class TypeAccessor
	{

	};


	/// <summary>
	/// Represents a reflectable type info per class
	/// </summary>
	class PORTAKAL_API Type
	{
		friend class FieldDispatcher;
		friend class AttributeDispatcher;
		friend class BaseTypeDispatcher;
	public:
		Type() = default;
		~Type() = default;

		/// <summary>
		/// Returns a field via name
		/// </summary>
		/// <param name="name"></param>
		/// <returns></returns>
		FORCEINLINE Field* GetField(const String& name);

		/// <summary>
		/// Returns all the fields
		/// </summary>
		/// <returns></returns>
		FORCEINLINE Array<Field*> GetFields() const noexcept { return mFields; }

		/// <summary>
		/// Returns all the fields with a access specifier filter
		/// </summary>
		/// <param name="specifier"></param>
		/// <returns></returns>
		FORCEINLINE Array<Field*> GetFields(const AccessSpecifier specifier);

		/// <summary>
		/// Returns the inherited base types
		/// </summary>
		/// <returns></returns>
		FORCEINLINE const Array<Type*>& GetBaseTypes() const noexcept { return mBaseTypes; }

		/// <summary>
		/// Returns whether this is a sub class of the given type
		/// </summary>
		/// <param name="pType"></param>
		/// <returns></returns>
		FORCEINLINE bool IsSubClassOf(const Type* pType) const noexcept;

		/*
		* Returns the attribute with the specified type
		*/
		FORCEINLINE Attribute* GetAttribute(const Type* pType) const noexcept;

		/// <summary>
		/// Returns a attribute which is attached to this type
		/// </summary>
		/// <typeparam name="TAttribute"></typeparam>
		/// <returns></returns>
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

		/// <summary>
		/// Returns the enum array
		/// </summary>
		/// <typeparam name="TEnum"></typeparam>
		/// <returns></returns>
		template<typename TEnum>
		Array<TEnum> GetEnums() const noexcept
		{
			Array<TEnum> enums;
			for (unsigned int i = 0; i < mEnums.GetCursor(); i++)
			{
				enums.Add((TEnum)mEnums[i].Value);
			}

			return enums;
		}

		/// <summary>
		/// Returns whether the specified enum name exists
		/// </summary>
		/// <param name="name"></param>
		/// <returns></returns>
		FORCEINLINE bool HasEnum(const String& name) const noexcept;

		/// <summary>
		/// Returns all the enum names
		/// </summary>
		/// <returns></returns>
		FORCEINLINE Array<String> GetEnumNames() const noexcept;

		/// <summary>
		/// Returns all the enum values
		/// </summary>
		/// <returns></returns>
		FORCEINLINE Array<long long> GetEnumValues() const noexcept;

		/// <summary>
		/// Returns the size of this type
		/// </summary>
		/// <returns></returns>
		FORCEINLINE virtual unsigned int GetSize() const noexcept = 0;

		/// <summary>
		/// Returns type name
		/// </summary>
		/// <returns></returns>
		FORCEINLINE virtual String GetTypeName() const noexcept = 0;

		/// <summary>
		/// Creates a defualt heap object
		/// </summary>
		/// <returns></returns>
		FORCEINLINE virtual void* CreateDefaultHeapObject() const noexcept = 0;

		/// <summary>
		/// Returns whether this type is a enum or not
		/// </summary>
		/// <returns></returns>
		FORCEINLINE virtual bool IsEnum() const noexcept { return false; }

		/// <summary>
		/// Returns whether this type is a primitive type or not
		/// </summary>
		/// <returns></returns>
		FORCEINLINE virtual bool IsPrimitive() const noexcept { return false; }

		/// <summary>
		/// Returns whether this type is a primitive type or not
		/// </summary>
		/// <returns></returns>
		FORCEINLINE virtual bool IsArray() const noexcept { return false; }

		/// <summary>
		/// Returns the type code of this type
		/// </summary>
		/// <returns></returns>
		FORCEINLINE virtual TypeCodes GetTypeCode() const noexcept { return TypeCodes::Composed; }
	protected:

		/// <summary>
		/// Internal base class register method
		/// </summary>
		/// <param name="pType"></param>
		void _RegisterBaseType(Type* pType);

		/// <summary>
		/// Internal field register method
		/// </summary>
		/// <param name="pField"></param>
		FORCEINLINE void _RegisterField(Field* pField);

		/// <summary>
		/// Internal attribute register method
		/// </summary>
		/// <param name="pAttribute"></param>
		FORCEINLINE void _RegisterAttribute(Attribute* pAttribute);

		/// <summary>
		/// Internal enum register method
		/// </summary>
		/// <param name="name"></param>
		/// <param name="value"></param>
		FORCEINLINE void _RegisterEnum(const String& name, const long long value);
	private:
		struct EnumEntry
		{
			String Name;
			long long Value;
		};
	private:
		Array<Field*> mFields;
		Array<Attribute*> mAttributes;
		Array<Type*> mBaseTypes;
		Array<EnumEntry> mEnums;
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



#define NO_DEFAULT_CONSTRUCTOR FORCEINLINE virtual void* CreateDefaultHeapObject() const noexcept override { return nullptr; }

#define HAS_DEFAULT_CONSTRUCTOR(type) FORCEINLINE virtual void* CreateDefaultHeapObject() const noexcept override { return new type(); }

#define typeof(type) TypeAccessor<type>::GetAccessorType()
}