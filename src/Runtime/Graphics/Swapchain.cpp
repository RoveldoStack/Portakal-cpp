#include "Swapchain.h"

namespace Portakal
{
	void Swapchain::Swapbuffers()
	{
		SwapbuffersCore();
	}
	void Swapchain::Resize(const unsigned int width, const unsigned int height)
	{
		ResizeCore(width, height);
		mWidth = width;
		mHeight = mHeight;
	}
	
}