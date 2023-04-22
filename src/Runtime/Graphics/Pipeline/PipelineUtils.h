#pragma once
#include <Runtime/Graphics/Pipeline/GraphicsPipelineCreateDesc.h>

namespace Portakal
{
	/// <summary>
	/// Utility class for the pipeline operations
	/// </summary>
	class PORTAKAL_API PipelineUtils
	{
	public:
		PipelineUtils() = delete;
		~PipelineUtils() = delete;

		/// <summary>
		/// Returns the input element data size
		/// </summary>
		/// <param name="format"></param>
		/// <returns></returns>
		FORCEINLINE static unsigned int GetInputElementDataSize(const InputElementDataFormat format);
	};
}