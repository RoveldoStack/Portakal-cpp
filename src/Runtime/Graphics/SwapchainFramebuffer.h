#pragma once
#include <Runtime/Graphics/Framebuffer.h>

namespace Portakal
{
	class PORTAKAL_API SwapchainFramebuffer : public Framebuffer
	{
	public:

	private:
		void _Resize(const unsigned int width, const unsigned int height);
	};
}