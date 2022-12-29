#pragma once
#include <Runtime/Core/Core.h>
#include <Runtime/Containers/String.h>

namespace Portakal
{
	/// <summary>
	/// Represents a simple GUID implementation
	/// </summary>
	class PORTAKAL_API Guid final
	{
	public:
		static Guid Create();
		static String ToString(const Guid& id);
		static Guid FromString(const String& text);
		static Guid Zero();
	public:
		Guid(unsigned int a, unsigned int b, unsigned int c, unsigned int d);
		Guid();
		~Guid();

		FORCEINLINE bool IsZero() const noexcept { return A == 0 && B == 0 && C == 0 && D == 0; }

		unsigned int A;
		unsigned int B;
		unsigned int C;
		unsigned int D;
	};

	PORTAKAL_API bool operator==(const Guid& a, const Guid& b);
	PORTAKAL_API bool operator!=(const Guid& a, const Guid& b);
}