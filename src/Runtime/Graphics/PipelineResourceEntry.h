#pragma once
#include <Runtime/Graphics/PipelineResourceType.h>
#include <Runtime/Containers/String.h>

namespace Portakal
{
	/// <summary>
	/// Pipeline resource specification
	/// </summary>
	struct PORTAKAL_API PipelineResourceEntry
	{
		/// <summary>
		/// Name of the resource
		/// </summary>
		String Name;

		/// <summary>
		/// Type of the resource
		/// </summary>
		PipelineResourceType Type;
	};
}