#include "DX12Fence.h"
#include <Runtime/DX12/DX12Device.h>
#include <Runtime/Assert/Assert.h>
namespace Portakal
{
	DX12Fence::DX12Fence(DX12Device* pDevice)
	{
		mEvent = CreateEvent(nullptr, FALSE, FALSE, nullptr);
		ASSERT(mEvent != nullptr, "DX12Device", "Failed to create the fence event");
	}
	DX12Fence::~DX12Fence()
	{

	}
}