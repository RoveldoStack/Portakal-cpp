#pragma once
#include <Runtime/Core/Core.h>

namespace Portakal
{
	/// <summary>
	/// Basic color structure and utilities
	/// </summary>
	/// <typeparam name="TData"></typeparam>
	template<typename TData>
	struct Color4
	{
		static Color4 Red() { return { 255,0,0,255 }; }
		static Color4 DarkRed() { return { 128,0,0,255 }; }
		static Color4 Black() { return { 0,0,0,255 }; }
		static Color4 Blue() { return { 0,0,256,255 }; }
		static Color4 DarkBlue() { return { 0,0,128,255 }; }
		static Color4 CornflowerBlue() { return { 100,149,237,255 }; }
		static Color4 Green() { return { 0,255,0,255 }; }
		static Color4 DarkGreen() { return { 0,128,0,255 }; }

		Color4(const TData r,const TData g,const TData b,const TData a) : R(r),G(g),B(b),A(a) {}
		Color4(const TData value) : R(value),G(value),B(value),A(value) {}
		Color4() : R(0),G(0),B(0),A(0) {}


		FORCEINLINE bool operator==(const Color4& other)
		{
			return R == other.R && G == other.G && B == other.B && A == other.A;
		}
		FORCEINLINE bool operator!=(const Color4& other)
		{
			return R != other.R || G != other.G || B != other.B || A != other.A;
		}

		TData R;
		TData G;
		TData B;
		TData A;
	};

	typedef Color4<unsigned char> ColorRgba;
	typedef Color4<float> ColorRgbaF;
}