#include "RenderingPath.h"
#include <Runtime/Graphics/GraphicsDevice.h>

namespace Portakal
{
	RenderingPath::RenderingPath(const GraphicsPipelineCreateDesc& desc, GraphicsDevice* pDevice) : mPipeline(nullptr)
	{
		/*
		* Create pipeline
		*/
		mPipeline = pDevice->CreateGraphicsPipeline(desc);

		mGraphicsDesc = desc;
	}
	RenderingPath::RenderingPath(const ComputePipelineCreateDesc& desc, GraphicsDevice* pDevice) : mPipeline(nullptr)
	{
		/*
		* Create pipeline
		*/
		mPipeline = pDevice->CreateComputePipeline(desc);

		mComputeDesc = desc;
	}
	RenderingPath::~RenderingPath()
	{
		if (mPipeline != nullptr)
			mPipeline->Destroy();

		mPipeline = nullptr;
		mGraphicsDesc = {};
		mComputeDesc = {};
	}
}