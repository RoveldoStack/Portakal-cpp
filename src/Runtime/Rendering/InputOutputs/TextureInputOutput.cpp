#include "TextureInputOutput.h"

namespace Portakal
{
	TextureInputOutput::TextureInputOutput(const String& name, RenderPass* pOwnerPass) : RenderPassInputOutput(name,pOwnerPass),mTexture(nullptr)
	{
	}
	TextureInputOutput::~TextureInputOutput()
	{
	}
	
	void TextureInputOutput::ForwardCore(void* pData)
	{
		mTexture = (TextureResource*)pData;
	}
}