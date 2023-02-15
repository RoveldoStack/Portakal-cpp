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
        LOG("Type", "Registered a base type: [%s] to the type: [%s]", *pType->GetTypeName(), *GetTypeName());
        mBaseTypes.Add(pType);
    }
    BaseTypeDispatcher::BaseTypeDispatcher(Type* pTargetType, Type* pBaseType)
    {
        pTargetType->_RegisterBaseType(pBaseType);
    }
}