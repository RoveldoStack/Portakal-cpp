#pragma once
#include <Runtime/Core/Core.h>
#include <Runtime/Resource/Material/MaterialParameterType.h>

namespace Portakal
{
	struct PORTAKAL_API MaterialParameterDescriptor
	{
		MaterialParameterType Type;
		Byte* pData;
		unsigned int SizeInBytes;
	};
}