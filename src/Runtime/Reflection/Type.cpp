#include "Type.h"
#include <Runtime/Reflection/Field.h>
#include <Runtime/Log/Log.h>

namespace Portakal
{
    Field* Type::GetField(const String& name)
    {
        for (unsigned int i = 0; i < mFields.GetCursor(); i++)
        {
            Field* pField = mFields[i];

            if (pField->GetFieldName() == name)
                return pField;
        }

        return nullptr;
    }
    Array<Field*> Type::GetFields(const AccessSpecifier specifier)
    {
        Array<Field*> fields;
        for (unsigned int i = 0; i < mFields.GetCursor(); i++)
        {
            Field* pField = mFields[i];
            if (pField->GetAccessSpecifier() & specifier)
                fields.Add(pField);
        }

        return fields;
    }
    bool Type::IsSubClassOf(const Type* pSubType) const noexcept
    {
        for (unsigned int i = 0; i < mBaseTypes.GetCursor(); i++)
        {
            Type* pBaseType = mBaseTypes[i];

            if (pBaseType == pSubType)
                return true;
        }

        for (unsigned int i = 0; i < mBaseTypes.GetCursor(); i++)
        {
            Type* pBaseType = mBaseTypes[i];

            if (pBaseType->IsSubClassOf(pSubType))
                return true;
        }

        return false;
    }
    void Type::_RegisterField(Field* pField)
    {
        mFields.Add(pField);
    }
    void Type::_RegisterAttribute(Attribute* pAttribute)
    {
        mAttributes.Add(pAttribute);
    }
    void Type::_RegisterEnum(const String& name, const long long value)
    {
        mEnums.Add({ name,value });
    }
    bool Type::HasEnum(const String& name) const noexcept
    {
        for (unsigned int i = 0; i < mEnums.GetCursor(); i++)
        {
            const EnumEntry& entry = mEnums[i];
            if (entry.Name == name)
                return true;
        }
        return false;
    }
    Array<String> Type::GetEnumNames() const noexcept
    {
        Array<String> names;
        for (unsigned int i = 0; i < mEnums.GetCursor(); i++)
        {
            const EnumEntry& entry = mEnums[i];
            names.Add(entry.Name);
        }
        return names;
    }
    Array<long long> Type::GetEnumValues() const noexcept
    {
        Array<long long> names;
        for (unsigned int i = 0; i < mEnums.GetCursor(); i++)
        {
            const EnumEntry& entry = mEnums[i];
            names.Add(entry.Value);
        }
        return names;
    }
    void Type::_RegisterBaseType(Type* pType)
    {
        mBaseTypes.Add(pType);
    }
    BaseTypeDispatcher::BaseTypeDispatcher(Type* pTargetType, Type* pBaseType)
    {
        LOG("Reflection", "Registered type %s to type %d", *pBaseType->GetTypeName(), *pTargetType->GetTypeName());
        pTargetType->_RegisterBaseType(pBaseType);
    }
}