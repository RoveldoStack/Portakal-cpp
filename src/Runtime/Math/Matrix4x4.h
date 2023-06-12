#pragma once
#include <Runtime/Core/Core.h>
#include <Runtime/Memory/Memory.h>
#include <Runtime/Math/Vector3.h>
#include <Runtime/Math/Vector2F.h>
#include <xmmintrin.h>
#include <immintrin.h>
namespace Portakal
{
	template<typename TType>
	struct Matrix4x4
	{
		static Matrix4x4 Translation(const Vector3<TType>& vector)
		{
			Matrix4x4 result =
			{
				1,0,0,0,
				0,1,0,0,
				0,0,1,0,
				vector.X,vector.Y,vector.Z,1
			};

			return result;
		}
		static Matrix4x4 Translation(const Vector2F& vector)
		{
			Matrix4x4 result =
			{
				1,0,0,0,
				0,1,0,0,
				0,0,1,0,
				vector.X,vector.Y,0,1
			};

			return result;
		}
		static Matrix4x4 Scale(const Vector3<TType>& vector)
		{
			Matrix4x4 result =
			{
				vector.X,0,0,0,
				0,vector.Y,0,0,
				0,0,vector.Z,0,
				0,0,0,1
			};

			return result;
		}
		static Matrix4x4 Scale(const Vector2F& vector)
		{
			Matrix4x4 result =
			{
				vector.X,0,0,0,
				0,vector.Y,0,0,
				0,0,1,0,
				0,0,0,1
			};

			return result;
		}
		static Matrix4x4 RotationX(const TType value)
		{
			const TType s = Math::Sin(value);
			const TType c = Math::Cos(value);
			Matrix4x4 result =
			{
				1,0,0,0,
				0,c,0,s,
				0,-s,0,c,
				0,0,0,1
			};

			return result;
		}
		static Matrix4x4 RotationY(const TType value)
		{
			const TType s = Math::Sin(value);
			const TType c = Math::Cos(value);
			Matrix4x4 result =
			{
				c,0,-s,0,
				0,1,0,0,
				s,0,c,0,
				0,0,0,1
			};

			return result;
		}
		static Matrix4x4 RotationZ(const TType value)
		{
			const TType s = Math::Sin(value);
			const TType c = Math::Cos(value);
			Matrix4x4 result =
			{
				c,-s,0,0,
				s,c,0,0,
				0,0,0,0,
				0,0,0,1
			};

			return result;
		}
		static Matrix4x4 Ortho(const TType left,const TType right,const TType bottom,const TType top, const TType near, const TType far)
		{
			Matrix4x4 result =
			{
				(TType)(2) / (right-left),0,0,0,
				0,(TType)(2) / (top-bottom),0,0,
				0,0,(TType)(2) / (far-near),0,
				(right + left) / (right - left),(top + bottom) / (top - bottom), (far + near) / (far-near)
			};

			return result;
		}
		static Matrix4x4 Ortho(const TType left, const TType right, const TType bottom, const TType top, const TType near, const TType far,const TType aspectRatio)
		{
			Matrix4x4 result =
			{
				(TType)(2) / (right - left),0,0,0,
				0,((TType)(2) / (top - bottom))*aspectRatio,0,0,
				0,0,(TType)(2) / (far - near),0,
				(right + left) / (right - left),(top + bottom) / (top - bottom), (far + near) / (far - near),1
			};
			return result;
		}
		static Matrix4x4 LookAt(const Vector3<TType>& position, const Vector3<TType>& lookPosition, const Vector3<TType>& upVector)
		{
			const Vector3<TType> f = (lookPosition - position).GetNormalized();
			const Vector3<TType> s = (Vector3<TType>::CrossProduct(f, upVector).GetNormalized);
			const Vector3<TType> u = (Vector3<TType>::CrossProduct(s, f));

			Matrix4x4 result =
			{
				s.X,u.X,-f.X,0,0,
				s.Y,u.Y,-f.Y,0,0,
				s.Z,u.Z,-f.Z,0,0,
				-Vector3<TType>::DotProduct(s,position),-Vector3<TType>::DotProduct(u,position),Vector3<TType>::DotProduct(f),position,1
			};

			return result;
		}
		static Matrix4x4 Perspective(const TType fov,const TType aspect,const TType near,const TType far)
		{
			Matrix4x4 result =
			{
				0,0,0,0,
				0,0,0,0,
				0,0,0,0,
				0,0,0,1
			};

			return result;
		}
		static Matrix4x4 Identity()
		{
			Matrix4x4 result =
			{1,0,0,0,
			 0,1,0,0,
			 0,0,1,0,
			 0,0,0,1};

			return result;
		}
		static Matrix4x4 Zero()
		{
			Matrix4x4 result =
			{0,0,0,0,
			 0,0,0,0,
			 0,0,0,0,
			 0,0,0,0 };

			return result;
		}
		constexpr Matrix4x4(
			const TType m00 = 0,
			const TType m01 = 0,
			const TType m02 = 0,
			const TType m03 = 0, 
			const TType m10 = 0,
			const TType m11 = 0, 
			const TType m12 = 0,
			const TType m13 = 0, 
			const TType m20 = 0,
			const TType m21 = 0, 
			const TType m22 = 0,
			const TType m23 = 0, 
			const TType m30 = 0,
			const TType m31 = 0,
			const TType m32 = 0,
			const TType m33 = 0 )
		{
			Values[0] = m00;
			Values[1] = m01;
			Values[2] = m02;
			Values[3] = m03;
			Values[4] = m10;
			Values[5] = m11;
			Values[6] = m12;
			Values[7] = m13;
			Values[8] = m20;
			Values[9] = m21;
			Values[10] = m22;
			Values[11] = m23;
			Values[12] = m30;
			Values[13] = m31;
			Values[14] = m32;
			Values[15] = m33;
		}
		constexpr Matrix4x4(const TType* pData)
		{
			Memory::Copy(pData, Values, sizeof(TType) * 16);
		}
		
		TType GetDeterminant() const noexcept
		{
			const TType a = 0;
			const TType b = 0;
			const TType c = 0;
			const TType d = 0;
			return 0;
		}
		bool IsInvertable() const noexcept
		{
			return GetDeterminant() != 0;
		}
		Matrix4x4 GetTransposed() const noexcept
		{
			Matrix4x4 result = {
			Values[0],Values[4],Values[8],Values[12],
			Values[1],Values[5],Values[9],Values[13],
			Values[2],Values[6],Values[10],Values[14],
			Values[3],Values[7],Values[11],Values[15] };

			return result;

		}
		Matrix4x4 GetInverted() const noexcept
		{
			if (!IsInvertable)
				return Matrix4x4::Zero();

			return {};
		}
		void Transpose() noexcept
		{
			Values[0] = Values[0]; Values[1] = Values[4]; Values[2] = Values[8]; Values[3] = Values[12];
			Values[4] = Values[1]; Values[5] = Values[5]; Values[6] = Values[9]; Values[7] = Values[13];
			Values[8] = Values[2]; Values[9] = Values[6]; Values[10] = Values[10]; Values[11] = Values[14];
			Values[12] = Values[3]; Values[13] = Values[7]; Values[14] = Values[11]; Values[15] = Values[15];
		}
		void Invert()
		{
			if (!IsInvertable())
				return;
		}
		
		TType Values[16];
	};

	template<typename TType>
	static Matrix4x4<TType> operator+(const Matrix4x4<TType>& const a, const Matrix4x4<TType>& const b)
	{
		Matrix4x4<TType> result = {};
		for (unsigned char i = 0; i < 16; i++)
			result.Values[i] = a.Values[i] + b.Values[i];

		return result;
	}
	template<typename TType>
	static Matrix4x4<TType> operator-(const Matrix4x4<TType>& const a, const Matrix4x4<TType>& const b)
	{
		Matrix4x4<TType> result = {};
		for (unsigned char i = 0; i < 16; i++)
			result.Values[i] = a.Values[i] - b.Values[i];

		return result;
	}
	template<typename TType>
	static Matrix4x4<TType> operator*(const Matrix4x4<TType>& const a, const Matrix4x4<TType>& const b)
	{
		Matrix4x4<TType> result = {};
		const TType m00 = a.Values[0] * b.Values[0] + a.Values[1] * b.Values[4] + a.Values[2] * b.Values[8] + a.Values[3] * b.Values[12];
		const TType m01 = a.Values[0] * b.Values[1] + a.Values[1] * b.Values[5] + a.Values[2] * b.Values[9] + a.Values[3] * b.Values[13];
		const TType m02 = a.Values[0] * b.Values[2] + a.Values[1] * b.Values[6] + a.Values[2] * b.Values[10] + a.Values[3] * b.Values[14];
		const TType m03 = a.Values[0] * b.Values[3] + a.Values[1] * b.Values[7] + a.Values[2] * b.Values[11] + a.Values[3] * b.Values[15];

		const TType m10 = a.Values[4] * b.Values[0] + a.Values[5] * b.Values[4] + a.Values[6] * b.Values[8] + a.Values[7] * b.Values[12];
		const TType m11 = a.Values[4] * b.Values[1] + a.Values[5] * b.Values[5] + a.Values[6] * b.Values[9] + a.Values[7] * b.Values[13];
		const TType m12 = a.Values[4] * b.Values[2] + a.Values[5] * b.Values[6] + a.Values[6] * b.Values[10] + a.Values[7] * b.Values[14];
		const TType m13 = a.Values[4] * b.Values[3] + a.Values[5] * b.Values[7] + a.Values[6] * b.Values[11] + a.Values[7] * b.Values[15];

		const TType m20 = a.Values[8] * b.Values[0] + a.Values[9] * b.Values[4] + a.Values[10] * b.Values[8] + a.Values[11] * b.Values[12];
		const TType m21 = a.Values[8] * b.Values[1] + a.Values[9] * b.Values[5] + a.Values[10] * b.Values[9] + a.Values[11] * b.Values[13];
		const TType m22 = a.Values[8] * b.Values[2] + a.Values[9] * b.Values[6] + a.Values[10] * b.Values[10] + a.Values[11] * b.Values[14];
		const TType m23 = a.Values[8] * b.Values[3] + a.Values[9] * b.Values[7] + a.Values[10] * b.Values[11] + a.Values[11] * b.Values[15];

		const TType m30 = a.Values[12] * b.Values[0] + a.Values[13] * b.Values[4] + a.Values[14] * b.Values[8] + a.Values[15] * b.Values[12];
		const TType m31 = a.Values[12] * b.Values[1] + a.Values[13] * b.Values[5] + a.Values[14] * b.Values[9] + a.Values[15] * b.Values[13];
		const TType m32 = a.Values[12] * b.Values[2] + a.Values[13] * b.Values[6] + a.Values[14] * b.Values[10] + a.Values[15] * b.Values[14];
		const TType m33 = a.Values[12] * b.Values[3] + a.Values[13] * b.Values[7] + a.Values[14] * b.Values[11] + a.Values[15] * b.Values[15];

		result.Values[0] = m00; result.Values[1] = m01; result.Values[2] = m02; result.Values[3] = m03;
		result.Values[4] = m10; result.Values[5] = m11; result.Values[6] = m12; result.Values[7] = m13;
		result.Values[8] = m20; result.Values[9] = m21; result.Values[10] = m22; result.Values[11] = m23;
		result.Values[12] = m30; result.Values[13] = m31; result.Values[14] = m32; result.Values[15] = m33;

		return result;
	}

	/*template<>
	struct Matrix4x4<float>
	{
		static Matrix4x4 Identity()
		{
			Matrix4x4 result =
			{ 1,0,0,0,
			 0,1,0,0,
			 0,0,1,0,
			 0,0,0,1 };

			return result;
		}
		static Matrix4x4 Zero()
		{
			Matrix4x4 result =
			{ 0,0,0,0,
			 0,0,0,0,
			 0,0,0,0,
			 0,0,0,0 };

			return result;
		}
		Matrix4x4(
			const float m00 = 0,
			const float m01 = 0,
			const float m02 = 0,
			const float m03 = 0,
			const float m10 = 0,
			const float m11 = 0,
			const float m12 = 0,
			const float m13 = 0,
			const float m20 = 0,
			const float m21 = 0,
			const float m22 = 0,
			const float m23 = 0,
			const float m30 = 0,
			const float m31 = 0,
			const float m32 = 0,
			const float m33 = 0)
		{

#ifdef PORTAKAL_SIMD_256
			Values[0] = _mm256_set_ps(m13, m12, m11, m10, m03, m02, m01, m00);
			Values[1] = _mm256_set_ps(m33, m32, m31, m30, m23, m22, m21, m20);
#endif
		}

		

		Matrix4x4 GetTransposed() const noexcept
		{
#ifdef PORTAKAL_SIMD_256
			Matrix4x4 result;
			result.Values[0] = _mm256_set_ps(
				Values[0].m256_f32[0], Values[0].m256_f32[4], Values[1].m256_f32[0], Values[1].m256_f32[4],
				Values[0].m256_f32[1], Values[0].m256_f32[5], Values[1].m256_f32[1], Values[1].m256_f32[5]
			);
			result.Values[1] = _mm256_set_ps(
				Values[0].m256_f32[2], Values[0].m256_f32[6], Values[1].m256_f32[2], Values[1].m256_f32[6],
				Values[0].m256_f32[3], Values[0].m256_f32[7], Values[1].m256_f32[3], Values[1].m256_f32[7]
			);
			return result;
#endif

		}
		void Transpose()
		{
#ifdef PORTAKAL_SIMD_256
			Values[0] = _mm256_set_ps(
				Values[0].m256_f32[0], Values[0].m256_f32[4], Values[1].m256_f32[0], Values[1].m256_f32[4],
				Values[0].m256_f32[1], Values[0].m256_f32[5], Values[1].m256_f32[1], Values[1].m256_f32[5]
			);
			Values[1] = _mm256_set_ps(
				Values[0].m256_f32[2], Values[0].m256_f32[6], Values[1].m256_f32[2], Values[1].m256_f32[6],
				Values[0].m256_f32[3], Values[0].m256_f32[7], Values[1].m256_f32[3], Values[1].m256_f32[7]
			);

#endif
		}
		Matrix4x4 operator+(const Matrix4x4& other)
		{
#ifdef PORTAKAL_SIMD_256
			Matrix4x4 result;
			result.Values[0] = _mm256_add_ps(this->Values[0], other.Values[0]);
			result.Values[1] = _mm256_add_ps(this->Values[1], other.Values[1]);
			
			return result;
;
#endif
			
		}
		Matrix4x4 operator-(const Matrix4x4& other)
		{
#ifdef PORTAKAL_SIMD_256
			Matrix4x4 result;
			result.Values[0] = _mm256_sub_ps(this->Values[0], other.Values[0]);
			result.Values[1] = _mm256_sub_ps(this->Values[1], other.Values[1]);

			return result;

#endif
		}

#ifdef PORTAKAL_SIMD_256
		__m256 Values[2];
#elif PORTAKAL_SIMD_512
		__m512 Values;
#endif

	};*/

	typedef Matrix4x4<float> Matrix4x4F;
	typedef Matrix4x4<double> Matrix4x4D;
}