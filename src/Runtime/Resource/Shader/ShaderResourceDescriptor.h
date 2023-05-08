#pragma once
#include <Runtime/Containers/String.h>
#include <Runtime/Graphics/Shader/ShaderStage.h>
#include <Runtime/Reflection/Type.h>

namespace Portakal
{
	PSTRUCT();
	struct PORTAKAL_API ShaderResourceDescriptor
	{
		ShaderResourceDescriptor() = default;
		~ShaderResourceDescriptor() = default;

		PFIELD();
		String Source;
		PFIELD();
		String EntryPoint;
		PFIELD();
		ShaderStage Stage;
	};

#include "ShaderResourceDescriptor.reflect.h"
}