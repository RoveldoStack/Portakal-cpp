#pragma once
#include <Runtime/Graphics/Shader/ShaderStage.h>
#include <Runtime/Containers/Array.h>
#include <Runtime/Containers/Registry.h>
#include <Runtime/Resource/Material/MaterialParameterDescriptor.h>

namespace Portakal
{
	struct PORTAKAL_API MaterialStageParameterDescriptor
	{
		Registry<String,MaterialParameterDescriptor> Parameters;
	};
}