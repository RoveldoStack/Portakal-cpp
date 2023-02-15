#include "DomainFile.h"
#include <Runtime/Platform/PlatformFile.h>
#include <Editor/Asset/IAssetSerializer.h>
#include <Editor/Asset/CustomAssetSerializerAttribute.h>
#include <Editor/Asset/IAssetVisualizer.h>
#include <Editor/Asset/CustomAssetVisualizerAttribute.h>
#include <Editor/Asset/SimpleTextAssetVisualizer.h>
#include <Runtime/Assert/Assert.h>
#include <Editor/Domain/DomainFileDescriptor.h>
#include <Runtime/Yaml/Yaml.h>

namespace Portakal
{

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
        * Setup
        */
        mID = fileDescriptor.ID;
        mResourceType = fileDescriptor.ResourceType;
        mName = PlatformFile::GetNameWithoutExtension(sourceFilePath);
        mSourceFilePath = sourceFilePath;
        mFileDescriptorPath = fileDescriptorPath;
        mOwnerFolder = pOwnerFolder;
        mSerializer = pSerializer;
        mVisualizer = pVisualizer;
        mSubObject = nullptr;
    }
    DomainFile::~DomainFile()
    {

    }
}