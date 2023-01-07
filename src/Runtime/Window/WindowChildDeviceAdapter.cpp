#include "WindowChildDeviceAdapter.h"
#include <Runtime/Window/Window.h>
#include <Runtime/Graphics/GraphicsDevice.h>
#include <Runtime/Assert/Assert.h>

namespace Portakal
{
	void WindowChildDeviceAdapter::_BindDeviceAndWindow(Window* pWindow, GraphicsDevice* pDevice)
	{
		ASSERT(pWindow == pDevice->GetOwnerWindow(), "WindowChildDeviceAdapter", "Device and window mismatch, this device does not belong to this window");

		pWindow->_SetChildDevice(pDevice);
	}
}