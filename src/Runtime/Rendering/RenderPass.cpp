#include "RenderPass.h"
#include <Runtime/Rendering/RenderGraph.h>

namespace Portakal
{
	RenderPass::RenderPass() : mOwnerGraph(nullptr)
	{

	}
	void RenderPass::MarkOwnerGraphDirty()
	{
		mOwnerGraph->_MarkGraphDirty();
	}

	void RenderPass::_ConnectInputTo(const String& name, RenderPassInputOutput* pIO)
	{
		/*
		* Try find input pin
		*/
		RenderPassInputOutput* pInput = GetInput(name);
		if (pInput == nullptr)
			return;

		/*
		* Connect pins
		*/
		pIO->ConnectOutputTo(pInput);
	}

	void RenderPass::_OnDelete()
	{
		/*
		* First finalize
		*/
		Finalize();

		/*
		* Remove input outputs
		*/
		for (unsigned int i = 0; i < mOutputs.GetCursor(); i++)
		{
			RenderPassInputOutput* pIO = mOutputs[i];
			pIO->_ClearInputOutputs();
		}

		/*
		* Clear the ios
		*/
		mOutputs.Clear();
		mInputs.Clear();

		/*
		* Remove the ownership
		*/
		mOwnerGraph = nullptr;
	}

	void RenderPass::ConnectOutputTo(const String& name, RenderPassInputOutput* pIO)
	{
		/*
		* Try find output pin
		*/
		RenderPassInputOutput* pOutput = GetOutput(name);
		if (pOutput == nullptr)
			return;
		/*
		* Check circular dependency
		*/
		if (IsPassDependent(pIO->GetOwnerPass()))
		{
			LOG("Renderpass", "Cannot ConnectOutputTo given IO has a circular dependency");
			return;
		}

		/*
		* Connect pins
		*/
		pIO->_ConnectInput(pOutput);
	}
	
	RenderPassInputOutput* RenderPass::GetInput(const String& name) const
	{
		for (unsigned int i = 0; i < mInputs.GetCursor(); i++)
			if (mInputs[i]->GetName() == name)
				return mInputs[i];

		return nullptr;
	}
	RenderPassInputOutput* RenderPass::GetOutput(const String& name) const
	{
		for (unsigned int i = 0; i < mOutputs.GetCursor(); i++)
			if (mOutputs[i]->GetName() == name)
				return mOutputs[i];

		return nullptr;
	}
	bool RenderPass::IsPassDependent(RenderPass* pPass) const
	{
		Array<RenderPassInputOutput*> inputs = pPass->GetInputs();
		for (unsigned int i = 0; i < inputs.GetCursor(); i++)
		{
			/*
			* Get and check inputIO
			*/
			RenderPassInputOutput* pIO = inputs[i];
			RenderPassInputOutput* pInputIO = pIO->GetInput();
			if (pInputIO == nullptr)
				continue;

			/*
			* Check if target pass has a input owner pass which is equals to this pass
			*/
			if (pInputIO->GetOwnerPass() == this)
				return true;

			/*
			* Check if target pass's inputs has a dependency towards this pass
			*/
			if (IsPassDependent(pInputIO->GetOwnerPass()))
				return true;
		}

		return false;
	}

	bool RenderPass::IsPassDependentOn(RenderPass* pPass) const
	{
		for (unsigned int i = 0; i < mInputs.GetCursor(); i++)
		{
			/*
			* Get and check inputIO
			*/
			RenderPassInputOutput* pIO = mInputs[i];
			RenderPassInputOutput* pInputIO = pIO->GetInput();
			if (pInputIO == nullptr)
				continue;

			/*
			* Check if target pass has a input owner pass which is equals to this pass
			*/
			if (pInputIO->GetOwnerPass() == this)
				return true;

			/*
			* Check if target pass's inputs has a dependency towards this pass
			*/
			if (IsPassDependent(pInputIO->GetOwnerPass()))
				return true;
		}

		return false;
	}
	
	void RenderPass::ForwardOutput(const String& name, void* pData) const
	{
		for (unsigned int i = 0; i < mOutputs.GetCursor(); i++)
		{
			RenderPassInputOutput* pIO = mOutputs[i];
			if (pIO->GetName() == name)
			{
				pIO->Forward(pData);
				return;
			}
		}
	}
}