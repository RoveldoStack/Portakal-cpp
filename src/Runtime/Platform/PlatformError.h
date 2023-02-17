#include <Runtime/Containers/String.h>

namespace Portakal
{
	class PORTAKAL_API PlatformError
	{
	public:
		PlatformError() = delete;
		~PlatformError() = delete;

		FORCEINLINE static String GetCurrentError();
	};
}