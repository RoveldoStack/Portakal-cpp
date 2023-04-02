#include "ResourceModule.h"
#include <Runtime/Resource/ResourceAPI.h>

namespace Portakal
{
    ResourceModule::ResourceModule()
    {

    }
    ResourceModule::~ResourceModule()
    {

    }
    void ResourceModule::OnInitialize()
    {

    }
    void ResourceModule::OnFinalize()
    {
        ResourceAPI::ClearResources();
    }
    void ResourceModule::OnPreTick()
    {

    }
    void ResourceModule::OnTick()
    {

    }
    void ResourceModule::OnPostTick()
    {

    }
    void ResourceModule::PreValidate()
    {

    }
    void ResourceModule::PostValidate()
    {

    }
    void ResourceModule::OnEvent(WindowEvent* pEvent)
    {

    }
}