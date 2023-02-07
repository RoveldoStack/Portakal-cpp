#pragma once
#include <Runtime/Graphics/PipelineResourceType.h>
#include <Runtime/Containers/String.h>

namespace Portakal
{
	struct PORTAKAL_API PipelineResourceEntry
	{
		String Name;
		PipelineResourceType Type;
	};
}