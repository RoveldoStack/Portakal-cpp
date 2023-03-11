#include "ResourceModule.h"
#include <Runtime/Resource/ResourceAPI.h>

namespace Portakal
{
    ResourceModule::ResourceModule() : mAPI(nullptr)
    {

    }
    ResourceModule::~ResourceModule()
    {

    }
    void ResourceModule::OnInitialize()
    {
        mAPI = new ResourceAPI();
    }
    void ResourceModule::OnFinalize()
    {
        delete mAPI;
        mAPI = nullptr;
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