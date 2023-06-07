#include "OtherInputOutput.h"

namespace Portakal
{
	OtherInputOutput::OtherInputOutput(const String& name, RenderPass* pOwnerPass) : RenderPassInputOutput(name,pOwnerPass),mData(nullptr)
	{

	}
	OtherInputOutput::~OtherInputOutput()
	{
		mData = nullptr;
	}
	void* OtherInputOutput::GetIOData() const noexcept
	{
		return mData;
	}
	RenderPassInputOutputType OtherInputOutput::GetIOType() const
	{
		return RenderPassInputOutputType::Other;
	}
	void OtherInputOutput::ForwardCore(void* pData)
	{
		mData = pData;
	}
}