#pragma once
#include <Runtime/Core/Core.h>
#include <Runtime/Math/Math.h>

namespace Portakal
{
	/// <summary>
	/// Templated vector2d implementation
	/// </summary>
	template<typename TValue>
	struct Vector2
	{
		/// <summary>
		/// Returns the dot product of the two vectors
		/// </summary>
		static TValue DotProduct(const Vector2& a, const Vector2& b)
		{
			return a.X * b.X + a.Y * b.Y;
		}

		Vector2(const TValue x, const TValue y) : X(x), Y(y) {}
		Vector2(const TValue value = 0) : X(value), Y(value) {}
		~Vector2() = default;

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
		FORCEINLINE Vector2 GetNormalized() const
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

		FORCEINLINE Vector2 operator+(const Vector2 other)
		{
			return { X + other.X,Y + other.Y };
		}
		FORCEINLINE Vector2 operator-(const Vector2 other)
		{
			return { X - other.X,Y - other.Y };
		}
		FORCEINLINE Vector2 operator*(const Vector2 other)
		{
			return { X * other.X,Y * other.Y };
		}
		FORCEINLINE Vector2 operator/(const Vector2 other)
		{
			return { X / other.X,Y / other.Y };
		}
		FORCEINLINE Vector2 operator+(const TValue value)
		{
			return { X + value, Y + value };
		}
		FORCEINLINE Vector2 operator-(const TValue value)
		{
			return { X - value, Y - value };
		}
		FORCEINLINE Vector2 operator*(const TValue value)
		{
			return { X * value, Y * value };
		}
		FORCEINLINE Vector2 operator/(const TValue value)
		{
			return { X / value, Y / value };
		}
		FORCEINLINE bool operator==(const Vector2 other)
		{
			return X == other.X && Y == other.Y;
		}
		FORCEINLINE bool operator!=(const Vector2 other)
		{
			return Y != other.X || Y == other.Y;
		}

		TValue X;
		TValue Y;
	};

	typedef Vector2<float> Vector2F;
	typedef Vector2<int> Vector2I;
	typedef Vector2<unsigned int> Vector2UI;
	typedef Vector2<double> Vector2D;

}