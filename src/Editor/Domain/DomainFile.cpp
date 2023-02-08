#include "DomainFile.h"
#include <Runtime/Platform/PlatformFile.h>
#include <Editor/Asset/IAssetSerializer.h>
#include <Editor/Asset/CustomAssetSerializerAttribute.h>
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
        * Find serialier
        */
        IAssetSerializer* pSerializer = nullptr;

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
        mSubObject = nullptr;
    }
    DomainFile::~DomainFile()
    {

    }
}