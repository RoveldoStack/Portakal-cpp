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

		FORCEINLINE const Array<ID3D11ShaderResourceView*>& GetDXSrvs() const noexcept { return mSrvsRaw; }
		FORCEINLINE const Array<ID3D11Buffer*>& GetDXBuffers() const noexcept { return mBuffers; }
		FORCEINLINE const Array<ID3D11SamplerState*>& GetDXSamplers() const noexcept { return mSamplers; }

		// Inherited via ResourceTable
		virtual void OnDestroy() override;
		virtual void* GetHandle() const noexcept override;
	private:
	
	private:
		Array<DXPTR<ID3D11ShaderResourceView>> mSrvs;
		Array<ID3D11ShaderResourceView*> mSrvsRaw;
		Array<ID3D11Buffer*> mBuffers;
		Array<ID3D11SamplerState*> mSamplers;
		

	};
}