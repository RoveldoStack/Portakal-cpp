#pragma once
#include <Runtime/Graphics/Pipeline/Resource/PipelineResourceTableDesc.h>
#include <Runtime/Graphics/Shader/ShaderStage.h>
namespace Portakal
{
	struct PORTAKAL_API PipelineResourceStageDesc
	{
		ShaderStage Stage;
		Array<PipelineResourceTableDesc> Tables;
	};
}