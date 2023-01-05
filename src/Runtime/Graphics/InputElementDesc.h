#pragma once
#include <Runtime/Graphics/InputElementDataFormat.h>
#include <Runtime/Graphics/InputElementSemantic.h>
#include <Runtime/Containers/String.h>

namespace Portakal
{
	struct PORTAKAL_API InputElementDesc
	{
		String Name;
		InputElementSemantic Semantic;
		InputElementDataFormat Format;
		unsigned int Offset;
	};
}