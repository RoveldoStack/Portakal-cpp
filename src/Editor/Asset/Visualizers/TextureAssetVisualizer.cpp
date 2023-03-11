#include "TextureAssetVisualizer.h"
#include <Editor/Domain/DomainFile.h>
#include <Runtime/Resource/Texture/TextureResource.h>
#include <Editor/Resource/EditorResourceAPI.h>
#include <Editor/Resource/EditorImageResource.h>
#include <Runtime/Resource/Resource.h>
namespace Portakal
{
	TextureResource* TextureAssetVisualizer::OnPaint(DomainFile* pFile)
	{
		if (!pFile->IsLoaded())
			pFile->LoadSync();

		TextureResource* pTexture = (TextureResource*)pFile->GetResource()->GetSubObject();

		return pTexture != nullptr ? pTexture : ((EditorImageResource*)EditorResourceAPI::GetResource("TextIcon.png"))->GetTexture();
	}
}