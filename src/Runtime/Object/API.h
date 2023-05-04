#pragma once
#include <Runtime/Core/Core.h>

namespace Portakal
{
	/// <summary>
	/// Represents a general application programming interface across the application's main dll boundry
	/// </summary>
	/// <typeparam name="TAPI"></typeparam>
	template<typename TAPI>
	class PORTAKAL_API API
	{
	protected:
		/// <summary>
		/// Returns the underlying API
		/// </summary>
		/// <returns></returns>
		static TAPI* GetUnderlyingAPI() noexcept { return sUnderlyingAPI; }
	private:
		static inline TAPI* sUnderlyingAPI = nullptr;
	public:
		API()
		{
			sUnderlyingAPI = (TAPI*)this;
		}
		virtual ~API()
		{
			sUnderlyingAPI = nullptr;
		}
	};
}