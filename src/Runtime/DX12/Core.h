#pragma 
#include <wrl/client.h>

using namespace Microsoft::WRL;

namespace Portakal
{
	class DX12Device;
	template<typename T>
	using DXPTR = ComPtr<T>;
}