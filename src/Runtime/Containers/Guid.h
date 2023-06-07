#pragma once
#include <Runtime/Core/Core.h>
#include <Runtime/Containers/String.h>
#include <Runtime/Reflection/Reflection.h>

namespace Portakal
{
	/// <summary>
	/// Represents a simple GUID implementation
	/// </summary>
	PSTRUCT();
	class PORTAKAL_API Guid final
	{
	public:
		/// <summary>
		/// Uses PlatfromGuid abstraction to create anew guid
		/// </summary>
		/// <returns></returns>
		static Guid Create();

		/// <summary>
		/// Creates empty guid(same with default constructor)
		/// </summary>
		/// <returns></returns>
		static Guid Zero();

		/// <summary>
		/// Converts guid to string
		/// </summary>
		/// <param name="id"></param>
		/// <returns></returns>
		static String ToString(const Guid& id);

		/// <summary>
		/// Returns Guid from string
		/// </summary>
		/// <param name="text"></param>
		/// <returns></returns>
		static Guid FromString(const String& text);

	public:
		Guid(UInt a, UInt b, UInt c, UInt d);
		Guid();
		~Guid();

		FORCEINLINE bool IsZero() const noexcept { return A == 0 && B == 0 && C == 0 && D == 0; }

		PFIELD();
		UInt A;
		PFIELD();
		UInt B;
		PFIELD();
		UInt C;
		PFIELD();
		UInt D;
	};

	PORTAKAL_API bool operator==(const Guid& a, const Guid& b);
	PORTAKAL_API bool operator!=(const Guid& a, const Guid& b);

#include "Guid.reflect.h"
}