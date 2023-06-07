#pragma once
#include <Runtime/Core/Core.h>

namespace Portakal
{
	/// <summary>
	/// Basic color structure and utilities
	/// </summary>
	/// <typeparam name="TData"></typeparam>
	struct Color4
	{
		static Color4 Red() { return Color4(255, 0, 0, 255); }
		static Color4 DarkRed() { return Color4(128,0,0,255); }
		static Color4 Black() { return Color4(0,0,0,255); }
		static Color4 Blue() { return Color4(0,0,256,255); }
		static Color4 DarkBlue() { return Color4(0,0,128,255); }
		static Color4 CornflowerBlue() { return Color4(100,149,237,255); }
		static Color4 Green() { return Color4(0,255,0,255); }
		static Color4 DarkGreen() { return Color4(0, 128, 0, 255); }

		Color4(const unsigned char r,const unsigned char g,const unsigned char b,const unsigned char a) : R(r),G(g),B(b),A(a) {}
		Color4(const unsigned char value) : R(value),G(value),B(value),A(value) {}
		Color4() : R(0),G(0),B(0),A(0) {}


		FORCEINLINE bool operator==(const Color4& other)
		{
			return R == other.R && G == other.G && B == other.B && A == other.A;
		}
		FORCEINLINE bool operator!=(const Color4& other)
		{
			return R != other.R || G != other.G || B != other.B || A != other.A;
		}

		unsigned char R;
		unsigned char G;
		unsigned char B;
		unsigned char A;
	};
}