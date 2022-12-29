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

		TValue X;
		TValue Y;
	};

	template<typename TValue>
	static Vector2<TValue> operator +(const Vector2<TValue>& a, const Vector2<TValue>& b)
	{
		return { a.X + b.X ,a.Y + b.Y };
	}
	template<typename TValue>
	static Vector2<TValue> operator -(const Vector2<TValue>& a, const Vector2<TValue>& b)
	{
		return { a.X - b.X ,a.Y - b.Y };
	}
	template<typename TValue>
	static Vector2<TValue> operator *(const Vector2<TValue>& a, const Vector2<TValue>& b)
	{
		return { a.X * b.X ,a.Y * b.Y };
	}
	template<typename TValue>
	static Vector2<TValue> operator /(const Vector2<TValue>& a, const Vector2<TValue>& b)
	{
		return { a.X / b.X ,a.Y / b.Y };
	}
	template<typename TValue>
	static Vector2<TValue> operator *(const Vector2<TValue>& a, const TValue scalar)
	{
		return { a.x * scalar,a.Y * scalar };
	}
	template<typename TValue>
	static Vector2<TValue> operator /(const Vector2<TValue>& a, const TValue scalar)
	{
		return { a.x / scalar,a.Y / scalar };
	}
	template<typename TValue>
	static bool operator ==(const Vector2<TValue>& a, const Vector2<TValue>& b)
	{
		return a.X == b.X && a.Y == b.Y;
	}
	template<typename TValue>
	static bool operator !=(const Vector2<TValue>& a, const Vector2<TValue>& b)
	{
		return a.X != b.X || a.Y != b.Y;
	}

}