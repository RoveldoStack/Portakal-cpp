#pragma once
#include <Runtime/Containers/Array.h>
#include <Runtime/Graphics/InputElementDesc.h>

namespace Portakal
{
	struct PORTAKAL_API InputLayoutDesc
	{
		Array<InputElementDesc> Elements;
		unsigned int InstanceStepRate;
	};
}