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

		/*
		* Mark the owner graph dirty
		*/
		if(mOwnerPass != nullptr)
			mOwnerPass->MarkOwnerGraphDirty();
	}

	void RenderPassInputOutput::ConnectOutputTo(RenderPass* pPass, const String& inputIOName)
	{
		/*
		* Connect input to
		*/
		pPass->_ConnectInputTo(inputIOName, this);

		/*
		* Mark the owner graph dirty
		*/
		if(mOwnerPass != nullptr)
			mOwnerPass->MarkOwnerGraphDirty();
	}

	void RenderPassInputOutput::_ConnectInput(RenderPassInputOutput* pIO)
	{
		mInput = pIO;
	}

	void RenderPassInputOutput::_ClearInputOutputs()
	{
		/*
		* First clear outputs
		*/
		for (unsigned int i = 0; i < mOutputs.GetCursor(); i++)
		{
			RenderPassInputOutput* pIO = mOutputs[i];
			pIO->_ConnectInput(nullptr);
		}

		/*
		* Clear the input pin
		*/
		_ConnectInput(nullptr);
	}

}