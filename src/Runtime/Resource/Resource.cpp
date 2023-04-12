#include "Resource.h"
#include <Runtime/Platform/PlatformFile.h>
#include <Runtime/Resource/IResourceSerializer.h>
#include <Runtime/Resource/ResourceSubObject.h>
#include <Runtime/Resource/CustomResourceSerializerAttribute.h>
#include <Runtime/Assert/Assert.h>
#include <Runtime/Resource/Scene/SceneSerializer.h>
#include <Runtime/Resource/ResourceLoadJob.h>
#include <Runtime/Job/JobSystem.h>
namespace Portakal
{
    SharedSafeHeap<ResourceSubObject> Resource::GetSubObject() const noexcept
    {
        mCriticalSection->Lock();
        SharedSafeHeap<ResourceSubObject> object = mSubObject;
        mCriticalSection->Release();

        return object;
    }
    ResourceSubObject* Resource::PeekSubObject() const noexcept
    {
        mCriticalSection->Lock();
        ResourceSubObject* pObject = mSubObject.GetHeap();
        mCriticalSection->Release();

        return pObject;
    }
    bool Resource::IsLoaded() const noexcept
    {
        mCriticalSection->Lock();
        const bool state = mLoaded;
        mCriticalSection->Release();

        return state;
    }
    bool Resource::IsCached() const noexcept
    {
        mCriticalSection->Lock();
        const bool state = mCached;
        mCriticalSection->Release();
        return state;
    }
    void Resource::LoadAsync()
    {
        /*
        * Return if already loaded
        */
        if (IsLoaded())
            return;

        /*
        * Validate and return if there's an alread working job
        */
        mCriticalSection->Lock();
        if (mLoadJob != nullptr && mLoadJob->IsFinished())
        {
            delete mLoadJob;
            mLoadJob = nullptr;
        }
        if (mLoadJob != nullptr)
        {
            mCriticalSection->Release();
            return;
        }

        /*
        * Validate if this resource has a serializer
        */
        if (mSerializer == nullptr)
        {
            mCriticalSection->Release();
            return;
        }

        mLoadJob = new ResourceLoadJob(mSerializer, mAbsolutePath, mByteOffset, mSize, GENERATE_MEMBER_DELEGATE1(this, Resource::OnResourceLoadedAsync, void, ResourceSubObject*));

        JobSystem::Schedule(mLoadJob);

        mCriticalSection->Release();
    }
    void Resource::UnloadAsync()
    {
        /*
        * Validate if loaded
        */
        if (!IsLoaded())
            return;

        /*
        * Validate if there is an ungoing job
        */
        mCriticalSection->Lock();
        if (mLoadJob != nullptr && mLoadJob->IsFinished())
        {
            delete mLoadJob;
            mLoadJob = nullptr;
        }
        if (mLoadJob != nullptr)
        {
            mCriticalSection->Release();
            return;
        }

        /*
        * Create job
        */
        mUnloadJob = nullptr;

        JobSystem::Schedule(mUnloadJob);

        mCriticalSection->Release();
    }
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
        mSubObject.Reset();
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
        : mSubObject(nullptr),mLoaded(false),mCompressed(bCompressed),mSerializer(nullptr),mCached(false), mLoadJob(nullptr),mUnloadJob(nullptr)
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
        mCriticalSection = PlatformCriticalSection::Create();
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
        mSubObject.Reset();

        mLoaded = false;
    }
    void Resource::OnResourceLoadedAsync(ResourceSubObject* pObject)
    {
        mCriticalSection->Lock();

        pObject->_SetOwnerResource(this);
        pObject->SetTagName(mName);
        pObject->OverrideID(mID);

        mSubObject = pObject;
        mLoaded = pObject != nullptr;

        mCriticalSection->Release();
    }
}