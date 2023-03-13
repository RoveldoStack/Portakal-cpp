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
        ByteBlock tempBlock = {};

        ASSERT(PlatformFile::Read(mAbsolutePath, tempBlock, mByteOffset, mByteOffset + mSize), "Resource", "Failed to load the file");

        ResourceSubObject* pSubObject = mCompressed ? mSerializer->DeserializeCompressed(tempBlock) : mSerializer->Deserialize(tempBlock);

        if (mType == "scene")
        {
            LOG("test", "est");
        }
        /*
        * Set resource
        */
        pSubObject->_SetOwnerResource(this);
        pSubObject->SetTagName(mName);

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
    Resource::Resource(const String& path, const String& resourceType,const bool bCompressed)
        : mSubObject(nullptr),mLoaded(false),mCompressed(bCompressed),mSerializer(nullptr)
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

            if (pAttribute->GetResourceType() != resourceType)
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
        mType = resourceType;
        mID = Guid::Create();
        mName = PlatformFile::GetName(path);
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