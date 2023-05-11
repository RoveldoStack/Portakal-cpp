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
		PipelineResourceTableDesc(const ShaderStage stage,const unsigned int startLocation,const Array<PipelineResourceEntry>& entries) : Stage(stage), StartLocation(startLocation), Entries(entries) {}
		PipelineResourceTableDesc() : Stage(ShaderStage::None), StartLocation(0) {}

		/// <summary>
		/// The starting location of the table
		/// </summary>
		unsigned int StartLocation;

		/// <summary>
		/// The shader stage it targets
		/// </summary>
		ShaderStage Stage;

		/// <summary>
		/// Resource specification entries
		/// </summary>
		Array<PipelineResourceEntry> Entries;
	};
}