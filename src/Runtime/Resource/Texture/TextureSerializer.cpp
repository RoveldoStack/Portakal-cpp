#include "TextureSerializer.h"
#include <Libs/Stbi/stb_image.h>

namespace Portakal
{
	ResourceSubObject* TextureSerializer::Deserialize(const ByteBlock& block)
	{
		/*
		* Load texture data from memory
		*/
		int width = -1;
		int height = -1;
		int channels = -1;

		unsigned char* pData = stbi_load_from_memory(block.GetBlockDataPtr(), block.GetBlockSizeInBytes(),&width,&height,&channels,4);

		/*
		* Validate dimensions
		*/
		if(width == 0 || height == 0 || channels == 0)
			return new TextureResource(TextureType::Texture2D, TextureUsage::ReadOnly, TextureFormat::R8_G8_B8_A8_UNorm, 512, 512, 0);;

		/*
		* Create texture data
		*/
		TextureResource* pTexture = new TextureResource(TextureType::Texture2D, TextureUsage::ReadOnly, TextureFormat::R8_G8_B8_A8_UNorm, width, height, 0);
		pTexture->UpdateTexture(pData, 0, 0, 0);

		/*
		* Release the temp data
		*/
		delete pData;

		return pTexture;
	}
	ResourceSubObject* TextureSerializer::DeserializeCompressed(const ByteBlock& block)
	{
		return nullptr;
	}
}