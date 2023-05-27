#include "RenderPassInputOutput.h"
#include <Runtime/Rendering/RenderPass.h>
namespace Portakal
{
	
	void RenderPassInputOutput::Forward(void* pData)
	{
		ForwardCore(pData);

		for (unsigned int i = 0; i < mOutputs.GetCursor(); i++)
			mOutputs[i]->Forward(pData);
	}
	void RenderPassInputOutput::ConnectOutputTo(RenderPassInputOutput* pIO)
	{
		/*
		* Register output
		*/
		mOutputs.Add(pIO);

		/*
		* Set other output io's input
		*/
		pIO->_ConnectInput(this);
	}

	void RenderPassInputOutput::ConnectOutputTo(RenderPass* pPass, const String& inputIOName)
	{
		pPass->_ConnectInputTo(inputIOName, this);
	}

	void RenderPassInputOutput::_ConnectInput(RenderPassInputOutput* pIO)
	{
		mInput = pIO;
	}

}