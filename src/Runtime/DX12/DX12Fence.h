#pragma once
#include <Runtime/Graphics/Fence.h>
#include <Runtime/DX12/Core.h>

namespace Portakal
{
	class PORTAKAL_API DX12Fence : public Fence
	{
	public:
		DX12Fence(DX12Device* pDevice);
		~DX12Fence();


	private:
		HANDLE mEvent;
		unsigned int mValue;
	};
}