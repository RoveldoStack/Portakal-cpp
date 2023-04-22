#include "Material.h"
#include <Runtime/Graphics/GraphicsDeviceAPI.h>
namespace Portakal
{
	Material::Material()
	{
		mOwnerDevice = GraphicsDeviceAPI::GetDefaultDevice();
	}
	Material::~Material()
	{
		mOwnerDevice = nullptr;
	}

	void Material::SetTextureParameter(const String& name, const ShaderStage stage, TextureResource* pTexture)
	{
		/*
		* Try find stage
		*/
		const int index = mParameterBlocks.FindIndex(stage);
		if (index == -1)
			return;

	}
	TextureResource* Material::GetTextureParameter(const String& name, const ShaderStage stage) const noexcept
	{
		return nullptr;
	}
	void Material::DestroyCore()
	{

	}
}