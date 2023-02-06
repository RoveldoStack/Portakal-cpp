#pragma once
#include <Runtime/Core/Core.h>

namespace Portakal
{
	#define PI 3.14159265359
	#define DEG_TO_RAD (2*PI) / 360
	#define RAD_TO_DEG 360 / (2*PI)

	/// <summary>
	/// General purpose math library
	/// </summary>
	class PORTAKAL_API Math
	{
	public:
		Math() = delete;
		~Math() = delete;

		FORCEINLINE static float Sqrt(const float value);
		FORCEINLINE static float Cos(const float rad);
		FORCEINLINE static float Sin(const float rad);
		FORCEINLINE static float Tan(const float rad);
		FORCEINLINE static float Abs(const float value);
	};
}