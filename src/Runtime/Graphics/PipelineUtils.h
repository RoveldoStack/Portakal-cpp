#pragma once
#include <Runtime/Graphics/GraphicsPipelineCreateDesc.h>

namespace Portakal
{
	class PORTAKAL_API PipelineUtils
	{
	public:
		PipelineUtils() = delete;
		~PipelineUtils() = delete;

		FORCEINLINE static unsigned int GetInputElementDataSize(const InputElementDataFormat format);
	};
}