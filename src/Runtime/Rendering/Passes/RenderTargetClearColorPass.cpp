#include "RenderTargetClearColorPass.h"
#include <Runtime/Resource/RenderTarget/RenderTargetResource.h>
#include <Runtime/Rendering/InputOutputs.h>

namespace Portakal
{
	RenderTargetClearColorPass::RenderTargetClearColorPass() : mClearColor(Color4::DarkGreen()),mRenderTarget(nullptr)
	{
		/*
		* Create input and outputs
		*/
		CreateInput<RenderTargetInputOutput>("rtIn");
		CreateInput<ColorRgbaInputOutput>("colorIn");
		CreateOutput<RenderTargetInputOutput>("rtOut");
	}
	RenderTargetClearColorPass::~RenderTargetClearColorPass()
	{

	}
	
	
	void RenderTargetClearColorPass::Initialize()
	{

	}
	void RenderTargetClearColorPass::Execute(CommandList* pCmdList) const
	{
		/*
		* Get render target 
		*/
		RenderTargetResource* pRtv = (RenderTargetResource*)GetInput("rtIn")->GetIOData();
		const Color4* clearColor = (Color4*)GetInput("colorIn")->GetIOData();

		if (pRtv != nullptr)
		{
			/*
			* Clear color
			*/
			pCmdList->BindFramebuffer(pRtv->GetFramebuffer());
			pCmdList->ClearColor(0, *clearColor);
		}

		/*
		* Get input
		*/
		ForwardOutput("rtOut",pRtv);
	}
	void RenderTargetClearColorPass::Finalize()
	{

	}
}