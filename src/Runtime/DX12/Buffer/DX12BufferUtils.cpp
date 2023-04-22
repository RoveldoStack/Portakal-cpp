#include "DX12BufferUtils.h"

namespace Portakal
{
	DXGI_FORMAT DX12BufferUtils::GetIndexFormat(const unsigned elementSizeInBytes)
	{
		switch (elementSizeInBytes)
		{
			case 2:
				return DXGI_FORMAT_R16_UINT;
			case 4:
				return DXGI_FORMAT_R32_UINT;
			case 8:
				return DXGI_FORMAT_R32G32_UINT;
		}

		if (elementSizeInBytes > 2 && elementSizeInBytes < 4)
			return DXGI_FORMAT_R32_UINT;
		if (elementSizeInBytes > 4 && elementSizeInBytes < 8)
			return DXGI_FORMAT_R32G32_UINT;

		return DXGI_FORMAT_R32_UINT;
	}
}