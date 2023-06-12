#pragma once
#include <Runtime/Core/Core.h>
#include <Runtime/Math/Math.h>

namespace Portakal
{
	/// <summary>
	/// Vector2UI implementation
	/// </summary>
	struct Vector2UI
	{
		/// <summary>
		/// Returns the dot product of the two vectors
		/// </summary>
		static unsigned int DotProduct(const Vector2UI& a, const Vector2UI& b)
		{
			return a.X * b.X + a.Y * b.Y;
		}

		constexpr Vector2UI(const unsigned int x, const unsigned int y) : X(x), Y(y) {}
		constexpr Vector2UI(const unsigned int value = 0) : X(value), Y(value) {}
		~Vector2UI() = default;

		/// <summary>
		/// Returns the length of the vector
		/// </summary>
		/// <returns></returns>
		FORCEINLINE unsigned int GetLength() const
		{
			return Math::Sqrt(X * X + Y * Y);
		}

		/// <summary>
		/// Returns the normalized version of this vector
		/// </summary>
		/// <returns></returns>
		FORCEINLINE Vector2UI GetNormalized() const
		{
			const unsigned int length = GetLength();
			return { X / length,Y / length };
		}

		/// <summary>
		/// Normalizes the vector
		/// </summary>
		FORCEINLINE void Normalize()
		{
			const unsigned int length = GetLength();
			X /= length;
			Y /= length;
		}

		FORCEINLINE Vector2UI operator+(const Vector2UI other)
		{
			return { X + other.X,Y + other.Y };
		}
		FORCEINLINE Vector2UI operator-(const Vector2UI other)
		{
			return { X - other.X,Y - other.Y };
		}
		FORCEINLINE Vector2UI operator*(const Vector2UI other)
		{
			return { X * other.X,Y * other.Y };
		}
		FORCEINLINE Vector2UI operator/(const Vector2UI other)
		{
			return { X / other.X,Y / other.Y };
		}
		FORCEINLINE Vector2UI operator+(const unsigned int value)
		{
			return { X + value, Y + value };
		}
		FORCEINLINE Vector2UI operator-(const unsigned int value)
		{
			return { X - value, Y - value };
		}
		FORCEINLINE Vector2UI operator*(const unsigned int value)
		{
			return { X * value, Y * value };
		}
		FORCEINLINE Vector2UI operator/(const unsigned int value)
		{
			return { X / value, Y / value };
		}
		FORCEINLINE bool operator==(const Vector2UI other)
		{
			return X == other.X && Y == other.Y;
		}
		FORCEINLINE bool operator!=(const Vector2UI other)
		{
			return Y != other.X || Y == other.Y;
		}

		unsigned int X;
		unsigned int Y;
	};
}