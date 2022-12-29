#include <Runtime/Core/Core.h>
#include <Runtime/Containers/Guid.h>

namespace Portakal
{
	/// <summary>
	/// Win32 implementation of the Guid
	/// </summary>
	class PORTAKAL_API Win32Guid
	{
	public:
		FORCEINLINE static void Create(Guid& id);
	public:
		Win32Guid() = delete;
		~Win32Guid() = delete;

	};
}