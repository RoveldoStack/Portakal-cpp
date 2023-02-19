#pragma once
#include <Runtime/Core/Core.h>

namespace Portakal
{
	class Type;

	/// <summary>
	/// Base reflecteable class
	/// </summary>
	class PORTAKAL_API Class
	{
	public:

		/// <summary>
		/// Returns the type
		/// </summary>
		/// <returns></returns>
		FORCEINLINE virtual Type* GetType() const noexcept = 0;
	};

#define GENERATE_CLASS(type) private:\
									friend class EMPTY(type)_Type;\
									static inline Type* sType = nullptr;\
								 public:\
									static void SetType(Type* pType) { sType = pType;}\
									FORCEINLINE virtual Type* GetType() const noexcept override { return sType;}
}