#pragma once
#include <Runtime/Containers/String.h>
#include <Runtime/Graphics/ShaderStage.h>
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

	//START_GENERATE_TYPE(ShaderObjectDescriptor);
	//START_TYPE_PROPERTIES(ShaderObjectDescriptor);
	//END_TYPE_PROPERTIES;
	//HAS_DEFAULT_CONSTRUCTOR(ShaderObjectDescriptor);
	//END_GENERATE_TYPE(ShaderObjectDescriptor);

#include "ShaderObjectDescriptor.reflect.h"
}