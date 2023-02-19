#pragma once
#include <Runtime/Graphics/ShaderStage.h>
#include <Runtime/Containers/Array.h>
#include <Runtime/Graphics/PipelineResourceEntry.h>

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