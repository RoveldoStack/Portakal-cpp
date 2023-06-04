#pragma once
#include <Runtime/Core/Core.h>
#include <Runtime/Resource/Material/MaterialParameterType.h>
#include <Runtime/Containers/String.h>

namespace Portakal
{
	struct PORTAKAL_API MaterialParameterDescriptor
	{
		MaterialParameterType Type;
		void* pData;
		unsigned int SizeInBytes;
	};
}