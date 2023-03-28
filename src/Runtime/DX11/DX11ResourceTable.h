#pragma once
#include <Runtime/DX11/Core.h>
#include <Runtime/Graphics/ResourceTable.h>
#include <d3d11.h>
namespace Portakal
{
	class PORTAKAL_API DX11ResourceTable : public ResourceTable
	{
	public:
		DX11ResourceTable(const ResourceTableCreateDesc& desc, DX11Device* pDevice);
		virtual ~DX11ResourceTable() override;

		// Inherited via ResourceTable
		virtual void OnDestroy() override;
		virtual void* GetHandle() const noexcept override;
	private:
	
	private:
		Array<ComPtr<ID3D11ShaderResourceView>> mSrvs;

	};
}