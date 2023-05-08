#include "MaterialResource.h"
#include <Runtime/Graphics/GraphicsDeviceAPI.h>
namespace Portakal
{
	MaterialResource::MaterialResource()
	{
		mOwnerDevice = GraphicsDeviceAPI::GetDefaultDevice();
	}
	MaterialResource::~MaterialResource()
	{
		mOwnerDevice = nullptr;
	}

	void MaterialResource::SetTextureParameter(const String& name, const ShaderStage stage, TextureResource* pTexture)
	{
		/*
		* Try find stage
		*/
		const int index = mParameterBlocks.FindIndex(stage);
		if (index == -1)
			return;

	}
	TextureResource* MaterialResource::GetTextureParameter(const String& name, const ShaderStage stage) const noexcept
	{
		return nullptr;
	}
	void MaterialResource::DestroyCore()
	{

	}
}