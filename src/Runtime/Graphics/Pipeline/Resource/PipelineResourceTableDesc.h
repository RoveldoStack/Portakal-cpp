#pragma once
#include <Runtime/Graphics/Shader/ShaderStage.h>
#include <Runtime/Containers/Array.h>
#include <Runtime/Graphics/Pipeline/Resource/PipelineResourceEntry.h>

namespace Portakal
{
	/// <summary>
	/// Pipeline resource specification table
	/// </summary>
	struct PORTAKAL_API PipelineResourceTableDesc
	{
		PipelineResourceTableDesc() : BufferOffset(0),TextureOffset(0),SamplerOffset(0),Stage(ShaderStage::None) {}
		~PipelineResourceTableDesc() = default;


		ShaderStage Stage;
		Array<PipelineResourceEntry> Buffers;
		Array<PipelineResourceEntry> Textures;
		Array<PipelineResourceEntry> Samplers;

		unsigned int BufferOffset;
		unsigned int TextureOffset;
		unsigned int SamplerOffset;
	};
}