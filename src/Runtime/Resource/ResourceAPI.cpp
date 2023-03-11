#include "ResourceAPI.h"
#include <Runtime/Platform/PlatformFile.h>
#include <Runtime/Message/MessageAPI.h>
#include <Runtime/Log/Log.h>

namespace Portakal
{
    ResourceAPI* ResourceAPI::sAPI = nullptr;

    Resource* ResourceAPI::GetResourceViaID(const Guid& id)
    {
        if (sAPI == nullptr)
            return nullptr;

        return sAPI->_GetResourceViaID(id);
    }
    Resource* ResourceAPI::RegisterResource(const String& path,const String& type)
    {
        if (sAPI == nullptr)
            return nullptr;

        return sAPI->_RegisterResource(path,type);
    }
    ResourceAPI::ResourceAPI(const String& packagesPath)
    {
        sAPI = this;
    }
    ResourceAPI::ResourceAPI()
    {
        sAPI = this;
    }
    ResourceAPI::~ResourceAPI()
    {
        /*
        * Clear resources
        */
        for (unsigned int i = 0; i < mResources.GetCursor(); i++)
        {
            Resource* pResource = mResources[i];

            LOG("ResourceAPI", "Delete resource %s", *pResource->GetAbsolutePath());

            delete pResource;
        }
        mResources.Clear();

        sAPI = nullptr;
    }
    Resource* ResourceAPI::_GetResourceViaID(const Guid& id)
    {
        for (unsigned int i = 0; i < mResources.GetCursor(); i++)
        {
            Resource* pResource = mResources[i];

            LOG("ResoureceAPI", "Deleted resource %s", *pResource->GetResourceType());

            if (pResource->GetID() == id)
                return pResource;
        }
        return nullptr;
    }
    Resource* ResourceAPI::_RegisterResource(const String& path,const String& type)
    {
        /*
        * Validate if there is a valid resource on the given path
        */
        if (!PlatformFile::IsExist(path))
            return nullptr;

        /*
        * Create resource
        */
        Resource* pResource = new Resource(path,type);

        mResources.Add(pResource);

        return pResource;
    }
}