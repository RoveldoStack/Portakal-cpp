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

namespace Portakal
{
    void DomainFile::LoadSync()
    {
        if (IsLoaded())
            return;

        mSubObject = mSerializer->Deserialize(this);
    }
    void DomainFile::UnloadSync()
    {
        if (!IsLoaded())
            return;

        if (mSubObject != nullptr)
            mSubObject->Destroy();

        mSubObject = nullptr;
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
        mSubObject = nullptr;
    }
    DomainFile::~DomainFile()
    {

    }
}