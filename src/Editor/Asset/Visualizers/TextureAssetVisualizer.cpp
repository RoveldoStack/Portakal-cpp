#include "TextureAssetVisualizer.h"
#include <Editor/Domain/DomainFile.h>
#include <Runtime/Resource/Texture/TextureResource.h>
#include <Editor/Resource/EditorResourceAPI.h>
#include <Editor/Resource/EditorImageResource.h>
#include <Runtime/Resource/Resource.h>
#include <memory>
namespace Portakal
{
	TextureResource* TextureAssetVisualizer::OnPaint(DomainFile* pFile)
	{
		if (!pFile->IsLoaded())
			pFile->LoadAsync();

		SharedHeap<TextureResource> pTexture = pFile->GetResource()->GetSubObject();

		return pTexture.GetHeap() != nullptr ? pTexture.GetHeap() : ((EditorImageResource*)EditorResourceAPI::GetResource("TextIcon.png"))->GetTexture();
	}
}