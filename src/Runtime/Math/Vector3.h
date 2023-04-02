#pragma once
#include <Runtime/Core/Core.h>
#include <Runtime/Math/Math.h>

namespace Portakal
{
	/// <summary>
	/// Templated vector2d implementation
	/// </summary>
	template<typename TValue>
	struct Vector3
	{
		/// <summary>
		/// Returns the dot product of the two vectors
		/// </summary>
		static TValue DotProduct(const Vector3& a, const Vector3& b)
		{
			return a.X * b.X + a.Y * b.Y + a.Z *b.Z; 
		}

		Vector3(const TValue x, const TValue y,const TValue z) : X(x), Y(y),Z(z) {}
		Vector3(const TValue value = 0) : X(value), Y(value),Z(value) {}
		~Vector3() = default;

		/// <summary>
		/// Returns the length of the vector
		/// </summary>
		/// <returns></returns>
		FORCEINLINE float GetLength() const
		{
			return Math::Sqrt(X * X + Y * Y + Z*Z);
		}

		/// <summary>
		/// Returns the normalized version of this vector
		/// </summary>
		/// <returns></returns>
		FORCEINLINE Vector3 GetNormalized() const
		{
			const float length = GetLength();
			return { X / length,Y / length,Z / length };
		}

		/// <summary>
		/// Normalizes the vector
		/// </summary>
		FORCEINLINE void Normalize()
		{
			const float length = GetLength();
			X /= length;
			Y /= length;
			Z /= length;
		}

		FORCEINLINE Vector3 operator+(const Vector3 other)
		{
			return { X + other.X,Y + other.Y ,other.X + other.Z};
		}
		FORCEINLINE Vector3 operator-(const Vector3 other)
		{
			return { X - other.X,Y - other.Y ,other.X - other.Z };
		}
		FORCEINLINE Vector3 operator*(const Vector3 other)
		{
			return { X * other.X,Y * other.Y ,other.X * other.Z };
		}
		FORCEINLINE Vector3 operator/(const Vector3 other)
		{
			return { X / other.X,Y / other.Y ,other.X / other.Z };
		}
		FORCEINLINE Vector3 operator+(const TValue value)
		{
			return { X + value, Y + value,Z + value };
		}
		FORCEINLINE Vector3 operator-(const TValue value)
		{
			return { X - value, Y - value,Z - value };
		}
		FORCEINLINE Vector3 operator*(const TValue value)
		{
			return { X * value, Y * value,Z * value };
		}
		FORCEINLINE Vector3 operator/(const TValue value)
		{
			return { X / value, Y / value,Z / value };
		}
		FORCEINLINE bool operator==(const Vector3 other)
		{
			return X == other.X && Y == other.Y && Z == other.Z;
		}
		FORCEINLINE bool operator!=(const Vector3 other)
		{
			return Y != other.X || Y != other.Y || Z != other.Z;
		}

		TValue X;
		TValue Y;
		TValue Z;
	};

	

}