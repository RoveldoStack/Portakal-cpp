#pragma once
#include <Runtime/Core/Core.h>
#include <Runtime/Memory/Memory.h>
#include <Runtime/Math/Vector3.h>
#include <Runtime/Math/Vector2.h>
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
				1,0,0,vector.X,
				0,1,0,vector.Y,
				0,0,1,vector.Z,
				0,0,0,1
			};

			return result;
		}
		static Matrix4x4 Translation(const Vector2<TType>& vector)
		{
			Matrix4x4 result =
			{
				1,0,0,vector.X,
				0,1,0,vector.Y,
				0,0,1,0,
				0,0,0,1
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
		static Matrix4x4 Scale(const Vector2<TType>& vector)
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
			const float s = Math::Sin(value);
			const float c = Math::Cos(value);
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
			const float s = Math::Sin(value);
			const float c = Math::Cos(value);
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
			const float s = Math::Sin(value);
			const float c = Math::Cos(value);
			Matrix4x4 result =
			{
				c,-s,0,0,
				s,c,0,0,
				0,0,0,0,
				0,0,0,1
			};

			return result;
		}
		static Matrix4x4 Orthographic(const TType size, const TType near, const TType far)
		{
			Matrix4x4 result =
			{
				1/size,0,0,1,
				0,1/size,0,1,
				0,0,-2/(far-near),-(far + near)/(far-near),
				0,0,0,1
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
		Matrix4x4(
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
		Matrix4x4(const TType* pData)
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
		Matrix4x4 operator+(const Matrix4x4& other)
		{
			Matrix4x4 result(this->Values);
			for (unsigned char i = 0; i < 16; i++)
				result.Values[i] += other.Values[i];

			return result;
		}
		Matrix4x4 operator-(const Matrix4x4& other)
		{
			Matrix4x4 result(this->Values);
			for (unsigned char i = 0; i < 16; i++)
				result.Values[i] -= other.Values[i];

			return result;
		}


		TType Values[16];
	};

	template<>
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

	};

	typedef Matrix4x4<float> Matrix4x4F;
	typedef Matrix4x4<double> Matrix4x4D;
}