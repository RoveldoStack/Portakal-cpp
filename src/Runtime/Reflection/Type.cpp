#include "Type.h"
#include <Runtime/Reflection/Field.h>
#include <Runtime/Log/Log.h>

namespace Portakal
{
    Field* Type::GetField(const String& name)
    {
        for (unsigned int i = 0; i < _fields.GetCursor(); i++)
        {
            Field* pField = _fields[i];

            if (pField->GetFieldName() == name)
                return pField;
        }

        return nullptr;
    }
    bool Type::IsSubClassOf(const Type* pSubType) const noexcept
    {
        for (unsigned int i = 0; i < _baseTypes.GetCursor(); i++)
        {
            Type* pBaseType = _baseTypes[i];

            if (pBaseType == pSubType)
                return true;
        }

        for (unsigned int i = 0; i < _baseTypes.GetCursor(); i++)
        {
            Type* pBaseType = _baseTypes[i];

            if (pBaseType->IsSubClassOf(pSubType))
                return true;
        }

        return false;
    }
    void Type::_RegisterField(Field* pField)
    {
        _fields.Add(pField);
    }
    void Type::_RegisterAttribute(Attribute* pAttribute)
    {
        _attributes.Add(pAttribute);
    }
    void Type::_RegisterBaseType(Type* pType)
    {
        LOG("Type", "Registered a base type: [%s] to the type: [%s]", *pType->GetTypeName(), *GetTypeName());
        _baseTypes.Add(pType);
    }
    BaseTypeDispatcher::BaseTypeDispatcher(Type* pTargetType, Type* pBaseType)
    {
        pTargetType->_RegisterBaseType(pBaseType);
    }
}