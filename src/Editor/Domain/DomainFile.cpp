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
#include <Editor/Asset/CustomAssetAuthoringToolAttribute.h>
#include <Editor/Asset/IAssetAuthoringTool.h>
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
        mSerializer->SerializeToEditor(mResource->PeekSubObject(), block);

        /*
        * Clear file content
        */
        PlatformFile::Delete(mSourceFilePath);
        PlatformFile::Create(mSourceFilePath);

        /*
        * Write
        */
        PlatformFile::Write(mSourceFilePath, block);
    }
    DomainFile::DomainFile(const String& fileDescriptorPath, DomainFolder* pOwnerFolder) :
        mValid(false),mAuthoringTool(nullptr),mSerializer(nullptr),mOwnerFolder(nullptr),mResource(nullptr),mVisualizer(nullptr)
    {
        /*
        * Load descriptor file
        */
        if (!PlatformFile::IsExist(fileDescriptorPath))
        {
            LOG("DomainFile", "Given domain file descriptor could not be found at %s", *fileDescriptorPath);
            return;
        }

        /*
        * Read descriptor
        */
        String fileContent;
        if (!PlatformFile::Read(fileDescriptorPath, fileContent))
        {
            LOG("DomainFile", "Could not read from domain file descriptor at %s", *fileDescriptorPath);
            return;
        }

        DomainFileDescriptor fileDescriptor = {};
        Yaml::ToObject(fileContent, &fileDescriptor);

        /*
        * Validate source file
        */
        const String sourceFilePath = PlatformFile::GetFileDirectory(fileDescriptorPath) + "\\" + fileDescriptor.SourceFile;
        ASSERT(PlatformFile::IsExist(sourceFilePath), "DomainFile", "Source file couldnt be found!");
        if (!PlatformFile::IsExist(sourceFilePath))
        {
            LOG("DomainFile", "Source file could not be found at %s", *sourceFilePath);
            return;
        }

        /*
        * Try create resource
        */
        const ResourceDescriptor descriptor = { fileDescriptor.ResourceType,fileDescriptor.ID };
        mResource = ResourceAPI::RegisterResource(sourceFilePath, descriptor);

        /*
        * Check if the resource is valid
        */
        if (mResource == nullptr)
        {
            LOG("DomainFile", "Could not create a valid resource %s",*fileDescriptor.SourceFile);
            return;
        }

        /*
        * Try find serializer
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
        * Validate found serializer
        */
        if (pSerializer == nullptr)
        {
            LOG("DomainFile", "Failed to find a suitable serializer for this domain file");
            return;
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
        IAssetAuthoringTool* pAuthoringTool = nullptr;
        for (unsigned int i = 0; i < types.GetCursor(); i++)
        {
            const Type* pType = types[i];

            if (!pType->IsSubClassOf(typeof(IAssetAuthoringTool)))
                continue;

            CustomAssetAuthoringToolAttribute* pAttribute = pType->GetAttribute<CustomAssetAuthoringToolAttribute>();
            if (pAttribute == nullptr)
                continue;

            if (pAttribute->GetResourceType() != fileDescriptor.ResourceType)
                continue;

            pAuthoringTool = (IAssetAuthoringTool*)pType->CreateDefaultHeapObject();
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
        mAuthoringTool = pAuthoringTool;
        mSerializer = pSerializer;
        mVisualizer = pVisualizer;
        mImporters = importers;
        mProcessors = processors;
        mOpenOperations = openOperations;
        mValid = true;
    }
    DomainFile::~DomainFile()
    {

    }
}