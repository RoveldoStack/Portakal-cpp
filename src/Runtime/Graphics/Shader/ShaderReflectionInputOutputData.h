#pragma once
#include <Runtime/Core/Core.h>
#include <Runtime/Graphics/Pipeline/Input/InputElementDataFormat.h>
#include <Runtime/Graphics/Pipeline/Input/InputElementSemantic.h>
namespace Portakal
{
	struct PORTAKAL_API ShaderReflectionInputOutputData
	{
		InputElementDataFormat Format;
		InputElementSemantic Semantic;
		unsigned char SemanticIndex;
		unsigned char RegisterIndex;
	};
}