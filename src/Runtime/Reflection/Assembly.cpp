#include "Assembly.h"
#include <Runtime/Reflection/Type.h>
#include <Runtime/Log/Log.h>
#include <Runtime/Log/Log.h>

namespace Portakal
{
    Assembly* Assembly::GetProcessAssembly() noexcept
    {
        if (sProcessAssembly == nullptr)
            sProcessAssembly = new Assembly();

        return sProcessAssembly;
    }
    Assembly::Assembly()
    {
        sProcessAssembly = this;
        LOG("Assembly", "Created new assembly");
    }
    Assembly::~Assembly()
    {
        sProcessAssembly = nullptr;
    }
    Type* Assembly::GetType(const String& name) const noexcept
    {
        for (unsigned int i = 0; i < _types.GetCursor(); i++)
        {
            Type* pType = _types[i];

            if (pType->GetTypeName() == name)
                return pType;
        }

        return nullptr;
    }
    void Assembly::RegisterType(Type* pType)
    {
        LOG("Assembly", "Registered type: %s", *pType->GetTypeName());
        _types.Add(pType);
    }
}