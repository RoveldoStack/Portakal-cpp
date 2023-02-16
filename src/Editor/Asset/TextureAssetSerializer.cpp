#include "TextureAssetSerializer.h"
#include <Runtime/Resource/Texture/TextureResource.h>
#include <Editor/Domain/DomainFile.h>

namespace Portakal
{
    void TextureAssetSerializer::SerializeToEditor(const ResourceSubObject* pObject)
    {
    }
    void TextureAssetSerializer::SerializeToPackage(const ResourceSubObject* pObject)
    {
    }
    ResourceSubObject* TextureAssetSerializer::Deserialize(const DomainFile* pFile)
    {
        TextureResource* pTexture = new TextureResource();
        pTexture->CreateTextureFromPath(pFile->GetSourceFilePath());

        return pTexture;
    }
}