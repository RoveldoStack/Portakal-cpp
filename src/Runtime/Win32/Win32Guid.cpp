#include "Win32Guid.h"
#include <Windows.h>
#include <Runtime/Assert/Assert.h>

namespace Portakal
{
	void Win32Guid::Create(Guid& id)
	{
		const HRESULT createHR = CoCreateGuid((GUID*)&id);
		ASSERT(SUCCEEDED(createHR), "Win32Guid", "Guid creation failed!");
	}
}