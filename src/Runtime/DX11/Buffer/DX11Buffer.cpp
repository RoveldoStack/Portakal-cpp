#include "DX11Buffer.h"
#include <Runtime/DX11/Buffer/DX11BufferUtils.h>
#include <Runtime/DX11/DX11Device.h>

namespace Portakal
{
	DX11Buffer::DX11Buffer(const GraphicsBufferCreateDesc& desc, DX11Device* pDevice) : GraphicsBuffer(desc)
	{
		D3D11_BUFFER_DESC bufferDesc = {};
		bufferDesc.ByteWidth = desc.SubItemSize*desc.SubItemCount;
		bufferDesc.StructureByteStride = desc.SubItemSize;
		bufferDesc.MiscFlags = 0;
		bufferDesc.CPUAccessFlags = DX11BufferUtils::GetCpuFlags(desc.Type);
		bufferDesc.Usage = DX11BufferUtils::GetUsage(desc.Type);

		pDevice->GetDXDevice()->CreateBuffer(&bufferDesc, nullptr, mBuffer.GetAddressOf());
	}
	DX11Buffer::~DX11Buffer()
	{
		mBuffer.Reset();
	}
	void DX11Buffer::OnDestroy()
	{
		mBuffer.Reset();
	}
}