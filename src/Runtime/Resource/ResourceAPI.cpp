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

            LOG("ResoureceAPI", "Deleted resource %s", *pResource->GetResourceType());

            if (pResource->GetID() == id)
                return pResource;
        }
        return nullptr;
    }
    Resource* ResourceAPI::RegisterResource(const String& path,const String& type)
    {
        /*
        * Validate if there is a valid resource on the given path
        */
        if (!PlatformFile::IsExist(path))
            return nullptr;

        /*
        * Create resource
        */
        Resource* pResource = new Resource(path, type);

        sResources.Add(pResource);

        return pResource;
    }
  
   
}