#include "ImGuiTextureBinding.h"
#include <Runtime/Graphics/GraphicsDevice.h>
#include <Runtime/Graphics/Resource/ResourceTable.h>
#include <Runtime/Resource/Texture/TextureResource.h>
#include <Runtime/Graphics/Texture/Texture.h>

namespace Portakal
{
	ImGuiTextureBinding::ImGuiTextureBinding(const TextureResource* pTexture) : mTargetTexture(pTexture),mTable(nullptr)
	{
		/*
		* Validate if target texture has a valid native texture
		*/
		Texture* pNativeTexture = pTexture->GetTexture();
		if (pNativeTexture == nullptr)
			return;

		/*
		* Create resource table
		*/
		ResourceTableCreateDesc tableDesc = {};
		tableDesc.Textures.Add(pNativeTexture);

		mTable = pNativeTexture->GetOwnerDevice()->CreateResourceTable(tableDesc);
		mTable->SetDeviceObjectName(pTexture->GetTagName());
	}
	ImGuiTextureBinding::~ImGuiTextureBinding()
	{
		if (mTable != nullptr)
			mTable->Destroy();

		mTable = nullptr;
	}
}