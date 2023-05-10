#include "DX11Buffer.h"
#include <Runtime/DX11/Buffer/DX11BufferUtils.h>
#include <Runtime/DX11/DX11Device.h>

namespace Portakal
{
	DX11Buffer::DX11Buffer(const GraphicsBufferCreateDesc& desc, DX11Device* pDevice) : GraphicsBuffer(desc)
	{
		/*
		* Get normalized size if this is a constant buffer
		*/
		unsigned int normalizedSize = desc.SubItemCount * desc.SubItemSize;
		if (desc.Type == GraphicsBufferType::ConstantBuffer)
		{
			if ((normalizedSize % 64) != 0)
				normalizedSize += 64 - (normalizedSize % 64);
		}

		D3D11_BUFFER_DESC bufferDesc = {};
		bufferDesc.ByteWidth = normalizedSize;
		bufferDesc.StructureByteStride = desc.SubItemSize;
		bufferDesc.MiscFlags = 0;
		bufferDesc.CPUAccessFlags = DX11BufferUtils::GetCpuFlags(desc.Type);
		bufferDesc.Usage = DX11BufferUtils::GetUsage(desc.Type);
		bufferDesc.BindFlags = DX11BufferUtils::GetBindFlags(desc.Type);

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