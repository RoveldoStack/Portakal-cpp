#include "ColorRgbaFInputOutput.h"

namespace Portakal
{
	ColorRgbaInputOutput::ColorRgbaInputOutput(const String& name, RenderPass* pOwnerPass) : RenderPassInputOutput(name,pOwnerPass)
	{
		mColor = Color4::DarkBlue(); // default
	}
	ColorRgbaInputOutput::~ColorRgbaInputOutput()
	{

	}
	void ColorRgbaInputOutput::ForwardCore(void* pData)
	{
		mColor = *(Color4*)pData;
	}
	void* ColorRgbaInputOutput::GetIOData() const noexcept
	{
		return (void*) & mColor;
	}
}