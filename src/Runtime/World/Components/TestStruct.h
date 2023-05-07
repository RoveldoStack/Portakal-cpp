#pragma once
#include <Runtime/Reflection/Reflection.h>

namespace Portakal
{
	PSTRUCT();
	struct PORTAKAL_API TestStruct
	{
		PFIELD();
		int A;
		PFIELD();
		int B;
		PFIELD();
		int C;
		PFIELD();
		String MyStr;
	};

#include "TestStruct.reflect.h"
}