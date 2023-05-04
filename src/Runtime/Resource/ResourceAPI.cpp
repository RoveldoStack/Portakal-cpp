#include "ResourceAPI.h"
#include <Runtime/Platform/PlatformFile.h>
#include <Runtime/Message/MessageAPI.h>
#include <Runtime/Log/Log.h>

namespace Portakal
{
    Array<Resource*> ResourceAPI::sResources;

    Resource* ResourceAPI::GetResourceViaID(const Guid& id)
    {
        for (unsigned int i = 0; i < sResources.GetCursor(); i++)
        {
            Resource* pResource = sResources[i];

            if (pResource->GetID() == id)
                return pResource;
        }
        return nullptr;
    }
    void ResourceAPI::ClearResources()
    {
        for (unsigned int i = 0; i < sResources.GetCursor(); i++)
        {
            Resource* pResource = sResources[i];
            delete pResource;
        }
        sResources.Clear();
    }
    Resource* ResourceAPI::RegisterResource(const String& path, const ResourceDescriptor& descriptor)
    {
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
        sResources.Add(pResource);

        return pResource;
    }
  
   
}