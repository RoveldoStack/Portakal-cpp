#pragma once
#include <Runtime/Containers/Array.h>
#include <Runtime/Graphics/PipelineResourceTableDesc.h>

namespace Portakal
{
	struct PORTAKAL_API ResourceStateDesc
	{
		Array<PipelineResourceTableDesc> Slots;
	};
}