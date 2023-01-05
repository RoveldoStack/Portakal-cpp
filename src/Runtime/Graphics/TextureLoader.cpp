#include "TextureLoader.h"
#include <Libs/Stbi/stb_image.h>
#include <Runtime/Graphics/TextureLoaderUtils.h>
namespace Portakal
{
	bool TextureLoader::LoadTextureFromDisk(const String& path, TextureLoadResult& resultOut)
	{
		int width = 0;
		int height = 0;
		int channels = 0;

		unsigned char* pData = stbi_load(path.GetSource(), &width, &height, &channels, 4);

		resultOut.Width = width;
		resultOut.Height = height;
		resultOut.Depth = 0;
		resultOut.Format = TextureLoaderUtils::GetTextureFormat(channels);
		resultOut.pData = pData;

		return pData != nullptr;
	}
}