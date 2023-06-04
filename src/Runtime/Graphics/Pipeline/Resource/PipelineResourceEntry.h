#pragma once
#include <Runtime/Graphics/Pipeline/Resource/PipelineResourceType.h>
#include <Runtime/Containers/String.h>
#include <Runtime/Graphics/Shader/ShaderStage.h>

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

		/*/// <summary>
		/// Type of the resource
		/// </summary>
		PipelineResourceType Type;*/

		///// <summary>
		///// The stage of the shader
		///// </summary>
		//ShaderStage Stage;
	};
}