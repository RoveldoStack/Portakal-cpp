#include "ColorRgbaFInputOutput.h"

namespace Portakal
{
	ColorRgbaInputOutput::ColorRgbaInputOutput(const String& name, RenderPass* pOwnerPass) : RenderPassInputOutput(name,pOwnerPass)
	{
		mColor = ColorRgbaF::DarkBlue(); // default
	}
	ColorRgbaInputOutput::~ColorRgbaInputOutput()
	{

	}
	void ColorRgbaInputOutput::ForwardCore(void* pData)
	{
		mColor = *(ColorRgbaF*)pData;
	}
	void* ColorRgbaInputOutput::GetIOData() const noexcept
	{
		return (void*) & mColor;
	}
}