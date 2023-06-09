#pragma once
#include <Runtime/Containers/Array.h>
#include <Runtime/Graphics/Pipeline/Resource/PipelineResourceStageDesc.h>

namespace Portakal
{
	/// <summary>
	/// Required information to specify the resource state of the pipeline
	/// </summary>
	struct PORTAKAL_API ResourceStateDesc
	{
		Array<PipelineResourceStageDesc> Stages;
	};
}