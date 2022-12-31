#include "Assembly.h"
#include <Runtime/Reflection/Type.h>

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
        _types.Add(pType);
    }
}