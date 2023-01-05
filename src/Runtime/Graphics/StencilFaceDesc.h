#pragma once
#include <Runtime/Core/Core.h>
#include <Runtime/Graphics/StencilOperation.h>
#include <Runtime/Graphics/ComparisionMethod.h>

namespace Portakal
{
	struct PORTAKAL_API StencilFaceDesc
	{
		StencilOperation Fail;
		StencilOperation Pass;
		StencilOperation DepthFail;
		ComparisionMethod Comparision;
	};
}

