#pragma once
#include <Runtime/DX11/Core.h>
#include <Runtime/Graphics/Buffer/GraphicsBuffer.h>
#include <d3d11.h>

namespace Portakal
{
	class PORTAKAL_API DX11Buffer : public GraphicsBuffer
	{
	public:
		DX11Buffer(const GraphicsBufferCreateDesc& desc,DX11Device* pDevice);
		virtual ~DX11Buffer() override;

		FORCEINLINE ID3D11Buffer* GetDXBuffer() const noexcept { return mBuffer.Get(); }

	private:
		virtual void OnDestroy() override;
		virtual void SetDeviceObjectNameCore(const String& name) override;
	private:
		DXPTR<ID3D11Buffer> mBuffer;
	};
}