#pragma once
#include <Runtime/Reflection/Reflection.h>
namespace Portakal
{
	PENUM();
	enum class PORTAKAL_API TestEnum : long long
	{
		A,
		B,
		C,
		D,
		E,
		F,
		G
	};
#include "TestEnum.reflect.h"
}