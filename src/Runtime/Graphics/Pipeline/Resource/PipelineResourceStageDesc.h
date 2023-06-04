#pragma once
#include <Runtime/Graphics/Pipeline/Resource/PipelineResourceTableDesc.h>
#include <Runtime/Graphics/Shader/ShaderStage.h>
namespace Portakal
{
	struct PORTAKAL_API PipelineResourceStageDesc
	{
		ShaderStage Stage;
		Array<PipelineResourceTableDesc> BufferTables;
		Array<PipelineResourceTableDesc> TextureTables;
		Array<PipelineResourceTableDesc> SamplerTables;

		unsigned int BufferOffset;
		unsigned int TextureOffset;
		unsigned int SamplerOffset;
	};
}