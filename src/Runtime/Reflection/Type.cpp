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