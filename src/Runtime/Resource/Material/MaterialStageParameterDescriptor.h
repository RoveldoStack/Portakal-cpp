#pragma once
#include <Runtime/Graphics/Shader/ShaderStage.h>
#include <Runtime/Containers/Array.h>
#include "MaterialParameterDescriptor.h"

namespace Portakal
{
	struct PORTAKAL_API MaterialStageParameterDescriptor
	{
		Array<MaterialParameterDescriptor> Parameters;
	};
}