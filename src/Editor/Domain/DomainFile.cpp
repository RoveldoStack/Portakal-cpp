#include "DomainFile.h"
#include <Runtime/Platform/PlatformFile.h>
#include <Editor/Asset/IAssetSerializer.h>
#include <Editor/Asset/CustomAssetSerializerAttribute.h>
#include <Editor/Asset/IAssetVisualizer.h>
#include <Editor/Asset/CustomAssetVisualizerAttribute.h>
#include <Editor/Asset/Visualizers/SimpleTextAssetVisualizer.h>
#include <Editor/Asset/CustomAssetImporterAttribute.h>
#include <Editor/Asset/IAssetImporter.h>
#include <Runtime/Assert/Assert.h>
#include <Editor/Domain/DomainFileDescriptor.h>
#include <Runtime/Yaml/Yaml.h>
#include <Editor/Asset/CustomAssetProcessorAttribute.h>
#include <Editor/Asset/IAssetProcessor.h>
#include <Runtime/Resource/ResourceSubObject.h>
#include <Editor/Asset/CustomAssetAuthorizationToolAttribute.h>
#include <Editor/Asset/IAssetAuthorizationTool.h>
#include <Editor/Domain/DomainFolder.h>
#include <Runtime/Resource/Resource.h>
#include <Runtime/Resource/ResourceAPI.h>
#include <Editor/Asset/IAssetOpenOperation.h>
#include <Editor/Asset/CustomAssetOpenOperationAttribute.h>
#include <Editor/Asset/Serializers/SceneAssetSerializer.h>

namespace Portakal
{
    bool DomainFile::IsLoaded() const noexcept
    {
        if (mResource == nullptr)
            return false;

        return mResource->IsLoaded();
    }
    void DomainFile::LoadAsync()
    {
        if (IsLoaded())
            return;

        mResource->LoadAsync();
    }
    void DomainFile::LoadSync()
    {
        if (IsLoaded())
            return;

        mResource->LoadSync();
    }
    void DomainFile::UnloadSync()
    {
        if (!IsLoaded())
            return;

        mResource->UnloadSync();
    }
    void DomainFile::Delete()
    {
        if (mOwnerFolder == nullptr)
            return;

        mOwnerFolder->DeleteFile(this);
    }
    void DomainFile::OpenSync()
    {
        LoadSync();

        for (unsigned int i = 0; i < mOpenOperations.GetCursor(); i++)
            mOpenOperations[i]->OnOpen(this);
    }
    void DomainFile::SaveSync()
    {
        /*
        * Validate if loaded
        */
        if (!IsLoaded())
            return;
        if (mSerializer == nullptr)
        {
            LOG("DomainFile", "Couldnt not SaveSync, cannot found serializer interface for type: %s", *mResourceType);
            return;
        }

        /*
        * Validate source file
        */
        ASSERT(PlatformFile::IsExist(mSourceFilePath), "DomainFile", "Couldnt found the file %s", *mSourceFilePath);

        /*
        * Deserialize into editor
        */
        ByteBlock block;
        mSerializer->SerializeToEditor(mResource->GetSubObject().GetHeap(), block);

        /*
        * Write
        */
        PlatformFile::Write(mSourceFilePath, block);
    }
    DomainFile::DomainFile(const String& fileDescriptorPath, DomainFolder* pOwnerFolder)
    {
        /*
        * Load descriptor file
        */
        ASSERT(PlatformFile::IsExist(fileDescriptorPath) , "DomainFile", "File descriptor couldnt be found!");

        /*
        * Read descriptor
        */
        String fileContent;
        ASSERT(PlatformFile::Read(fileDescriptorPath, fileContent), "DomainFile", "Failed to read the file descriptor");

        DomainFileDescriptor fileDescriptor = {};
        Yaml::ToObject(fileContent, &fileDescriptor);

        /*
        * Validate source file
        */
        const String sourceFilePath = PlatformFile::GetFileDirectory(fileDescriptorPath) + "\\" + fileDescriptor.SourceFile;
        ASSERT(PlatformFile::IsExist(sourceFilePath), "DomainFile", "Source file couldnt be found!");

        /*
        * Create resource
        */
        const ResourceDescriptor descriptor = { fileDescriptor.ResourceType,fileDescriptor.ID };
        mResource = ResourceAPI::RegisterResource(sourceFilePath, descriptor);

        /*
        * Find serializer
        */
        IAssetSerializer* pSerializer = nullptr;
        const Array<Type*> types = Assembly::GetProcessAssembly()->GetTypes();
        for (unsigned int i = 0; i < types.GetCursor(); i++)
        {
            const Type* pType = types[i];

            if (!pType->IsSubClassOf(typeof(IAssetSerializer)))
                continue;

            CustomAssetSerializerAttribute* pAttribute = pType->GetAttribute<CustomAssetSerializerAttribute>();
            if (pAttribute == nullptr)
                continue;

            if (pAttribute->GetResourceType() != fileDescriptor.ResourceType)
                continue;

            pSerializer = (IAssetSerializer*)pType->CreateDefaultHeapObject();
            break;
        }

        /*
        * Find visualizer
        */
        IAssetVisualizer* pVisualizer = nullptr;
        for (unsigned int i = 0; i < types.GetCursor(); i++)
        {
            const Type* pType = types[i];

            if (!pType->IsSubClassOf(typeof(IAssetVisualizer)))
                continue;

            CustomAssetVisualizerAttribute* pAttribute = pType->GetAttribute<CustomAssetVisualizerAttribute>();
            if (pAttribute == nullptr)
                continue;

            if (pAttribute->GetResourceType() != fileDescriptor.ResourceType)
                continue;

            pVisualizer = (IAssetVisualizer*)pType->CreateDefaultHeapObject();
            break;
        }

        /*
        * Find importers
        */
        Array<IAssetImporter*> importers;
        for (unsigned int i = 0; i < types.GetCursor(); i++)
        {
            const Type* pType = types[i];

            if (!pType->IsSubClassOf(typeof(IAssetImporter)))
                continue;

            CustomAssetImporterAttribute* pAttribute = pType->GetAttribute<CustomAssetImporterAttribute>();
            if (pAttribute == nullptr)
                continue;

            if (pAttribute->GetResourceType() != fileDescriptor.ResourceType)
                continue;

            importers.Add((IAssetImporter*)pType->CreateDefaultHeapObject());
        }

        /*
        * Find processors
        */
        Array<IAssetProcessor*> processors;
        for (unsigned int i = 0; i < types.GetCursor(); i++)
        {
            const Type* pType = types[i];

            if (!pType->IsSubClassOf(typeof(IAssetImporter)))
                continue;

            CustomAssetProcessorAttribute* pAttribute = pType->GetAttribute<CustomAssetProcessorAttribute>();
            if (pAttribute == nullptr)
                continue;

            if (pAttribute->GetResourceType() != fileDescriptor.ResourceType)
                continue;

            processors.Add((IAssetProcessor*)pType->CreateDefaultHeapObject());
        }

        /*
        * Find authorization tool
        */
        IAssetAuthorizationTool* pAuthorizationTool = nullptr;
        for (unsigned int i = 0; i < types.GetCursor(); i++)
        {
            const Type* pType = types[i];

            if (!pType->IsSubClassOf(typeof(IAssetAuthorizationTool)))
                continue;

            CustomAssetAuthorizationToolAttribute* pAttribute = pType->GetAttribute<CustomAssetAuthorizationToolAttribute>();
            if (pAttribute == nullptr)
                continue;

            if (pAttribute->GetResourceType() != fileDescriptor.ResourceType)
                continue;

            pAuthorizationTool = (IAssetAuthorizationTool*)pType->CreateDefaultHeapObject();
            break;
        }

        /*
        * Find open operations
        */
        Array<IAssetOpenOperation*> openOperations;
        for (unsigned int i = 0; i < types.GetCursor(); i++)
        {
            const Type* pType = types[i];

            if (!pType->IsSubClassOf(typeof(IAssetOpenOperation)))
                continue;

            const CustomAssetOpenOperationAttribute* pAttribute = pType->GetAttribute<CustomAssetOpenOperationAttribute>();
            if (pAttribute == nullptr)
                continue;
            if (pAttribute->GetResourceType() != fileDescriptor.ResourceType)
                continue;

            openOperations.Add((IAssetOpenOperation*)pType->CreateDefaultHeapObject());
        }

        /*
        * Setup
        */
        mID = fileDescriptor.ID;
        mResourceType = fileDescriptor.ResourceType;
        mName = PlatformFile::GetNameWithoutExtension(sourceFilePath);
        mSourceFilePath = sourceFilePath;
        mFileDescriptorPath = fileDescriptorPath;
        mOwnerFolder = pOwnerFolder;
        mAuthorizationTool = pAuthorizationTool;
        mSerializer = pSerializer;
        mVisualizer = pVisualizer;
        mImporters = importers;
        mProcessors = processors;
        mOpenOperations = openOperations;

    }
    DomainFile::~DomainFile()
    {

    }
}