#include "ImGuiTextureBinding.h"
#include <Runtime/Graphics/GraphicsDevice.h>
#include <Runtime/Graphics/ResourceTable.h>
#include <Runtime/Resource/Texture/TextureResource.h>
#include <Runtime/Graphics/Texture.h>

namespace Portakal
{
	ImGuiTextureBinding::ImGuiTextureBinding(const TextureResource* pTexture) : mTargetTexture(pTexture),mTable(nullptr)
	{
		Texture* pNativeTexture = pTexture->GetTexture();
		if (pNativeTexture == nullptr)
			return;

		ResourceTableCreateDesc tableDesc = {};
		tableDesc.Resources.Add(pNativeTexture);

		mTable = pNativeTexture->GetOwnerDevice()->CreateResourceTable(tableDesc);
	}
	ImGuiTextureBinding::~ImGuiTextureBinding()
	{
		if (mTable != nullptr)
			mTable->DeleteDeviceObject();

		mTable = nullptr;
	}
}