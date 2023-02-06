#pragma once
#include <Runtime/Core/Core.h>
#include <d3d12.h>

namespace Portakal
{
	class PORTAKAL_API DX12Resource
	{
	public:
		DX12Resource()
		{
			MutateDXResourceState(D3D12_RESOURCE_STATE_COPY_DEST);
		}
		~DX12Resource() = default;

		FORCEINLINE D3D12_RESOURCE_STATES GetDXResourceState() const noexcept { return mState; }
		FORCEINLINE void MutateDXResourceState(D3D12_RESOURCE_STATES state) noexcept { mState = state; }
	private:
		D3D12_RESOURCE_STATES mState;
	};
}