#include "DX11BufferUtils.h"
#include <Runtime/Assert/Assert.h>

namespace Portakal
{
	D3D11_USAGE DX11BufferUtils::GetUsage(GraphicsBufferType type)
	{
		switch (type)
		{
		case Portakal::GraphicsBufferType::VertexBuffer:
		case Portakal::GraphicsBufferType::IndexBuffer:
		case Portakal::GraphicsBufferType::ConstantBuffer:
			return D3D11_USAGE_DYNAMIC;
		default:
			ASSERT(false, "DX11BufferUtils", "Invalid GraphicsBufferType");
			break;
		}
		return D3D11_USAGE_DEFAULT;
	}
	D3D11_CPU_ACCESS_FLAG DX11BufferUtils::GetCpuFlags(const GraphicsBufferType type)
    {
		switch (type)
		{
		case Portakal::GraphicsBufferType::VertexBuffer:
		case Portakal::GraphicsBufferType::IndexBuffer:
		case Portakal::GraphicsBufferType::ConstantBuffer:
			return D3D11_CPU_ACCESS_WRITE;
		default:
			ASSERT(false, "DX11BufferUtils", "Invalid GraphicsBufferType");
			break;
		}
		return D3D11_CPU_ACCESS_WRITE;
    }
}