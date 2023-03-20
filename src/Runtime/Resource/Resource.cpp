#include "Resource.h"
#include <Runtime/Platform/PlatformFile.h>
#include <Runtime/Resource/IResourceSerializer.h>
#include <Runtime/Resource/ResourceSubObject.h>
#include <Runtime/Resource/CustomResourceSerializerAttribute.h>
#include <Runtime/Assert/Assert.h>
#include <Runtime/Resource/Scene/SceneSerializer.h>

namespace Portakal
{
    void Resource::LoadSync()
    {
        /*
        * Validate if has a serializer
        */
        if (mSerializer == nullptr)
            return;

        /*
        * Deserialize object
        */
        ResourceSubObject* pSubObject = nullptr;
        if (mCached)
        {
            pSubObject = mCompressed ? mSerializer->DeserializeCompressed(mCachedData) : mSerializer->Deserialize(mCachedData);
        }
        else
        {
            ByteBlock tempBlock = {};
            ASSERT(PlatformFile::Read(mAbsolutePath, tempBlock, mByteOffset, mByteOffset + mSize), "Resource", "Failed to load the file");
            pSubObject = mCompressed ? mSerializer->DeserializeCompressed(tempBlock) : mSerializer->Deserialize(tempBlock);
        }

        /*
        * Set resource
        */
        pSubObject->_SetOwnerResource(this);
        pSubObject->SetTagName(mName);
        pSubObject->OverrideID(mID);

        mSubObject = pSubObject;

        mLoaded = true;
    }
    void Resource::UnloadSync()
    {
        /*
        * Validate if has a serializer
        */
        if (mSerializer == nullptr)
            return;

        /*
        * Validate if loaded
        */
        if (!mLoaded)
            return;

        /*
        * Delete the resource
        */
        delete mSubObject;
        mSubObject = nullptr;
        mLoaded = false;
    }
    void Resource::CacheSync()
    {
        if (mCached)
            return;

        ASSERT(PlatformFile::Read(mAbsolutePath, mCachedData, mByteOffset, mByteOffset + mSize), "Resource", "Failed to load the file");

        mCached = true;
    }
    void Resource::ClearCacheSync()
    {
        if (!mCached)
            return;

        mCachedData.Clear();

        mCached = false;
    }
    Resource::Resource(const String& path,const ResourceDescriptor& descriptor,const bool bCompressed)
        : mSubObject(nullptr),mLoaded(false),mCompressed(bCompressed),mSerializer(nullptr),mCached(false)
    {
        /*
        * Get custom resource serializer
        */
        const Array<Type*> types = Assembly::GetProcessAssembly()->GetTypes();
        Type* pFoundType = nullptr;
        for (unsigned int i = 0; i < types.GetCursor(); i++)
        {
            Type* pType = types[i];

            /*
            * Validate sub class
            */
            if (!pType->IsSubClassOf(typeof(IResourceSerializer)))
                continue;

            /*
            * Validate attribute
            */
            const CustomResourceSerializerAttribute* pAttribute = pType->GetAttribute<CustomResourceSerializerAttribute>();
            if (pAttribute == nullptr)
                continue;

            if (pAttribute->GetResourceType() != descriptor.ResourceType)
            {
                continue;
            }

            pFoundType = pType;
        }

        /*
        * Create serializer
        */
        if (pFoundType != nullptr)
            mSerializer = (IResourceSerializer*)pFoundType->CreateDefaultHeapObject();

        /*
        * Setup
        */
        mAbsolutePath = path;
        mType = descriptor.ResourceType;
        mID = descriptor.ID;
        mName = PlatformFile::GetNameWithoutExtension(path);
        mByteOffset = 0;
        mSize = PlatformFile::GetSize(path);
    }
    Resource::~Resource()
    {
        /*
        * Validate if has a serializer
        */
        if (mSerializer == nullptr)
            return;

        delete mSerializer;
        mSerializer = nullptr;

        /*
        * Validate if loaded
        */
        if (!mLoaded)
            return;

        /*
        * Delete the resource
        */
        mSubObject->Destroy();

        delete mSubObject;

        mSubObject = nullptr;
        mLoaded = false;
    }
}