#pragma once
#include <Runtime/Containers/Array.h>
#include <Runtime/Graphics/PipelineResourceTableDesc.h>

namespace Portakal
{
	/// <summary>
	/// Required information to specify the resource state of the pipeline
	/// </summary>
	struct PORTAKAL_API ResourceStateDesc
	{
		/// <summary>
		/// The specifications
		/// </summary>
		Array<PipelineResourceTableDesc> Slots;
	};
}