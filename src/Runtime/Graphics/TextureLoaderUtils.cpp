#include "TextureLoaderUtils.h"

namespace Portakal
{
	TextureFormat TextureLoaderUtils::GetTextureFormat(const unsigned int channels)
	{
		return TextureFormat::R8_G8_B8_A8_UNorm;
	}
}