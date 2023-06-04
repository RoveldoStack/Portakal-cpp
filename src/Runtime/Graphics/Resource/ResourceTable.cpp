#include "ResourceTable.h"

namespace Portakal
{
	ResourceTable::ResourceTable(const ResourceTableCreateDesc& desc) : mBuffers(desc.Buffers),mTextures(desc.Textures),mSamplers(desc.Samplers)
	{
		mHasBuffers = desc.Buffers.GetCursor() > 0;
		mHasTextures = desc.Textures.GetCursor() > 0;
		mHasSamplers = desc.Samplers.GetCursor() > 0;

	}
}