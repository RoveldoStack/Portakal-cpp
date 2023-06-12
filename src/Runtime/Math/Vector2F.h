#pragma once
#include <Runtime/Core/Core.h>
#include <Runtime/Math/Math.h>
#include <Runtime/Reflection/Reflection.h>

namespace Portakal
{
	/// <summary>
	/// Vector2F implementation
	/// </summary>
	PSTRUCT();
	struct Vector2F
	{
		/// <summary>
		/// Returns the dot product of the two vectors
		/// </summary>
		static float DotProduct(const Vector2F& a, const Vector2F& b)
		{
			return a.X * b.X + a.Y * b.Y;
		}

		constexpr Vector2F(const float x, const float y) : X(x), Y(y) {}
		constexpr Vector2F(const float value = 0) : X(value), Y(value) {}
		~Vector2F() = default;

		/// <summary>
		/// Returns the length of the vector
		/// </summary>
		/// <returns></returns>
		FORCEINLINE float GetLength() const
		{
			return Math::Sqrt(X * X + Y * Y);
		}

		/// <summary>
		/// Returns the normalized version of this vector
		/// </summary>
		/// <returns></returns>
		FORCEINLINE Vector2F GetNormalized() const
		{
			const float length = GetLength();
			return { X / length,Y / length };
		}

		/// <summary>
		/// Normalizes the vector
		/// </summary>
		FORCEINLINE void Normalize()
		{
			const float length = GetLength();
			X /= length;
			Y /= length;
		}

		FORCEINLINE Vector2F operator+(const Vector2F other)
		{
			return { X + other.X,Y + other.Y };
		}
		FORCEINLINE Vector2F operator-(const Vector2F other)
		{
			return { X - other.X,Y - other.Y };
		}
		FORCEINLINE Vector2F operator*(const Vector2F other)
		{
			return { X * other.X,Y * other.Y };
		}
		FORCEINLINE Vector2F operator/(const Vector2F other)
		{
			return { X / other.X,Y / other.Y };
		}
		FORCEINLINE Vector2F operator+(const float value)
		{
			return { X + value, Y + value };
		}
		FORCEINLINE Vector2F operator-(const float value)
		{
			return { X - value, Y - value };
		}
		FORCEINLINE Vector2F operator*(const float value)
		{
			return { X * value, Y * value };
		}
		FORCEINLINE Vector2F operator/(const float value)
		{
			return { X / value, Y / value };
		}
		FORCEINLINE bool operator==(const Vector2F other)
		{
			return X == other.X && Y == other.Y;
		}
		FORCEINLINE bool operator!=(const Vector2F other)
		{
			return Y != other.X || Y == other.Y;
		}

		PFIELD();
		float X;
		PFIELD();
		float Y;
	};

#include "Vector2F.reflect.h"
}