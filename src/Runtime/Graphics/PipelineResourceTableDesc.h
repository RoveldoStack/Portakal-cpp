#pragma once
#include <Runtime/Graphics/ShaderStage.h>
#include <Runtime/Containers/Array.h>
#include <Runtime/Graphics/PipelineResourceEntry.h>

namespace Portakal
{
	struct PORTAKAL_API PipelineResourceTableDesc
	{
		ShaderStage Stage;
		Array<PipelineResourceEntry> Slots;
	};
}