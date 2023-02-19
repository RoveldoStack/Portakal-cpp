#include <Runtime/Containers/String.h>

namespace Portakal
{
	/// <summary>
	/// Platform agnstic error management class
	/// </summary>
	class PORTAKAL_API PlatformError
	{
	public:
		PlatformError() = delete;
		~PlatformError() = delete;

		/// <summary>
		/// Returns the latests platform error message
		/// </summary>
		/// <returns></returns>
		FORCEINLINE static String GetCurrentError();
	};
}