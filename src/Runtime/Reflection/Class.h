#pragma once
#include <Runtime/Core/Core.h>

namespace Portakal
{
	class Type;

	class PORTAKAL_API Class
	{
	public:
		FORCEINLINE virtual Type* GetType() const noexcept = 0;
	};

#define GENERATE_CLASS(type) private:\
									friend class EMPTY(type)_Type;\
									static inline Type* sType = nullptr;\
								 public:\
									static void SetType(Type* pType) { sType = pType;}\
									FORCEINLINE virtual Type* GetType() const noexcept override { return sType;}
}