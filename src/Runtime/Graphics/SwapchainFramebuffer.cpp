#include "SwapchainFramebuffer.h"
#include <Runtime/DX12/DX12Device.h>
#include <Runtime/Log/Log.h>

namespace Portakal
{
	void SwapchainFramebuffer::_Resize(const unsigned int width, const unsigned int height)
	{
		ResizeCore(width, height);
		SetWidth(width);
		SetHeight(height);
	}
	OutputDesc SwapchainFramebuffer::GetOutputDesc() const noexcept
	{
		OutputDesc outputDesc = {};
		outputDesc.ColorAttachments.Add({ _swapchainColorFormat });
		outputDesc.DepthStencilAttachment.Format = _swapchainDepthStencilFormat;
		outputDesc.SampleCount = 1;

		return outputDesc;
	}

}