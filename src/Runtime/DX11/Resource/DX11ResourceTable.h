#pragma once
#include <Runtime/DX11/Core.h>
#include <Runtime/Graphics/Resource/ResourceTable.h>
#include <d3d11.h>
namespace Portakal
{
	class PORTAKAL_API DX11ResourceTable : public ResourceTable
	{
	public:
		DX11ResourceTable(const ResourceTableCreateDesc& desc, DX11Device* pDevice);
		virtual ~DX11ResourceTable() override;

		FORCEINLINE const Array<ID3D11ShaderResourceView*>& GetDXResourceViews() const noexcept { return mResourceViews; }
		FORCEINLINE const Array<ID3D11Buffer*>& GetDXBuffers() const noexcept { return mBuffers; }
		FORCEINLINE const Array<ID3D11SamplerState*>& GetDXSamplers() const noexcept { return mSamplers; }

	private:
		// Inherited via ResourceTable
		virtual void OnDestroy() override;
		virtual void SetDeviceObjectNameCore(const String& name) override;
	private:
		Array<ID3D11ShaderResourceView*> mResourceViews;
		Array<ID3D11Buffer*> mBuffers;
		Array<ID3D11SamplerState*> mSamplers;
		

	};
}