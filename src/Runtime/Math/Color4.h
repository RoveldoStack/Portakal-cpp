#pragma once
#include <Runtime/Core/Core.h>

namespace Portakal
{
	typedef Color4<unsigned char> ColorRgba;
	typedef Color4<float> ColorRgbaF;

	template<typename TData>
	struct Color4
	{
		Color4() : R(0),G(0),B(0),A(0) {}

		TData R;
		TData G;
		TData B;
		TData A;
	};
}