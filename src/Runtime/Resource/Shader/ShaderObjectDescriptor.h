#pragma once
#include <Runtime/Containers/String.h>
#include <Runtime/Graphics/Shader/ShaderStage.h>
#include <Runtime/Reflection/Type.h>

namespace Portakal
{
	struct PORTAKAL_API ShaderObjectDescriptor : public Class
	{
		GENERATE_CLASS(ShaderObjectDescriptor);

		ShaderObjectDescriptor() = default;
		~ShaderObjectDescriptor() = default;

		String Source;
		String EntryPoint;
		ShaderStage Stage;
	};

#include "ShaderObjectDescriptor.reflect.h"
}