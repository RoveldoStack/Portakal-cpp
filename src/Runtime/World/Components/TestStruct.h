#pragma once
#include <Runtime/Reflection/Reflection.h>

namespace Portakal
{
	class PORTAKAL_API TestStruct : public Class
	{
		GENERATE_CLASS(TestStruct);
	public:

		FIELD();
		int A;
		FIELD();
		int B;
		FIELD();
		int C;
		FIELD();
		String MyStr;
	};

#include "TestStruct.reflect.h"
}