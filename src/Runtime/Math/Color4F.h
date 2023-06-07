#pragma once
#include <Runtime/Core/Core.h>

namespace Portakal
{
	/// <summary>
	/// Basic color structure and utilities
	/// </summary>
	/// <typeparam name="TData"></typeparam>
	struct Color4F
	{
		static Color4F Red() { return Color4F(255, 0, 0, 255); }
		static Color4F DarkRed() { return Color4F(128, 0, 0, 255); }
		static Color4F Black() { return Color4F(0, 0, 0, 255); }
		static Color4F Blue() { return Color4F(0, 0, 256, 255); }
		static Color4F DarkBlue() { return Color4F(0, 0, 128, 255); }
		static Color4F CornflowerBlue() { return Color4F(100, 149, 237, 255); }
		static Color4F Green() { return Color4F(0, 255, 0, 255); }
		static Color4F DarkGreen() { return Color4F(0, 128, 0, 255); }

		Color4F(const float r, const float g, const float b, const float a) : R(r), G(g), B(b), A(a) {}
		Color4F(const float value) : R(value), G(value), B(value), A(value) {}
		Color4F() : R(0), G(0), B(0), A(0) {}


		FORCEINLINE bool operator==(const Color4F& other)
		{
			return R == other.R && G == other.G && B == other.B && A == other.A;
		}
		FORCEINLINE bool operator!=(const Color4F& other)
		{
			return R != other.R || G != other.G || B != other.B || A != other.A;
		}

		float R;
		float G;
		float B;
		float A;
	};
}