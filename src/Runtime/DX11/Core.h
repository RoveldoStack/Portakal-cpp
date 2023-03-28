#pragma once
#include <wrl/client.h>

using namespace Microsoft::WRL;

namespace Portakal
{
	class DX11Device;
	template<typename T>
	using DXPTR = ComPtr<T>;
}