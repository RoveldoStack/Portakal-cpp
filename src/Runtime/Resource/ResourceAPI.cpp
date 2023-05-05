#include "ResourceAPI.h"
#include <Runtime/Platform/PlatformFile.h>
#include <Runtime/Message/MessageAPI.h>
#include <Runtime/Log/Log.h>

namespace Portakal
{
    Resource* ResourceAPI::GetResourceViaID(const Guid& id)
    {
        ResourceAPI* pAPI = GetUnderlyingAPI();
        if (pAPI == nullptr)
            return nullptr;

        for (unsigned int i = 0; i < pAPI->mResources.GetCursor(); i++)
        {
            Resource* pResource = pAPI->mResources[i];

            if (pResource->GetID() == id)
                return pResource;
        }
        return nullptr;
    }
    void ResourceAPI::ClearResources()
    {
        ResourceAPI* pAPI = GetUnderlyingAPI();
        if (pAPI == nullptr)
            return;

        for (unsigned int i = 0; i < pAPI->mResources.GetCursor(); i++)
        {
            Resource* pResource = pAPI->mResources[i];
            delete pResource;
        }
        pAPI->mResources.Clear();
    }
    ResourceAPI::ResourceAPI()
    {
    }
    ResourceAPI::~ResourceAPI()
    {
    }
    Resource* ResourceAPI::RegisterResource(const String& path, const ResourceDescriptor& descriptor)
    {
        ResourceAPI* pAPI = GetUnderlyingAPI();
        if (pAPI == nullptr)
            return nullptr;

        /*
        * Validate if there is a valid resource on the given path
        */
        if (!PlatformFile::IsExist(path))
            return nullptr;

        /*
        * Try create resource
        */
        Resource* pResource = new Resource(path,descriptor);

        /*
        * Validate if resource is valid
        */
        if (!pResource->IsValid())
        {
            delete pResource;
            return nullptr;
        }

        /*
        * Register resources
        */
        pAPI->mResources.Add(pResource);

        return pResource;
    }
  
   
}