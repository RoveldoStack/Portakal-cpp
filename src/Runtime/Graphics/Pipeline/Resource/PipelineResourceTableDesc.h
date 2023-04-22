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
		/// <summary>
		/// The shader stage it targets
		/// </summary>
		ShaderStage Stage;

		/// <summary>
		/// Resource specification entries
		/// </summary>
		Array<PipelineResourceEntry> Slots;
	};
}