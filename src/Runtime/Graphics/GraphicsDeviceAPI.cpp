#include "GraphicsDeviceAPI.h"

namespace Portakal
{
	Array<GraphicsDevice*> GraphicsDeviceAPI::sDevices;
	Array<GraphicsDevice*> GraphicsDeviceAPI::sStandaloneDevices;
	Array<GraphicsDevice*> GraphicsDeviceAPI::sWindowedDevices;

	GraphicsDevice* GraphicsDeviceAPI::GetDefaultDevice()
	{
		if (sWindowedDevices.GetCursor() > 0)
			return sWindowedDevices[0];
		if (sStandaloneDevices.GetCursor() > 0)
			return sStandaloneDevices[0];

		return nullptr;
	}
	GraphicsDevice* GraphicsDeviceAPI::GetDefaultWindowedDevice()
	{
		if (sWindowedDevices.GetCursor() > 0)
			return sWindowedDevices[0];
		return nullptr;
	}
	GraphicsDevice* GraphicsDeviceAPI::GetDefaultStandaloneDevice()
	{
		if (sStandaloneDevices.GetCursor() > 0)
			return sStandaloneDevices[0];

		return nullptr;
	}
	Array<GraphicsDevice*> GraphicsDeviceAPI::GetAllDevices()
	{
		return sDevices;
	}
	Array<GraphicsDevice*> GraphicsDeviceAPI::GetWindowedDevices()
	{
		return sWindowedDevices;
	}
	Array<GraphicsDevice*> GraphicsDeviceAPI::GetStandaloneDevices()
	{
		return sStandaloneDevices;
	}
	void GraphicsDeviceAPI::RegisterStandaloneDevice(GraphicsDevice* pDevice)
	{
		sStandaloneDevices.Add(pDevice);
		sDevices.Add(pDevice);
	}
	void GraphicsDeviceAPI::RemoveStandaloneDevice(GraphicsDevice* pDevice)
	{
		sStandaloneDevices.Remove(pDevice);
		sDevices.Remove(pDevice);
	}
	void GraphicsDeviceAPI::RegisterWindowedDevice(GraphicsDevice* pDevice)
	{
		sWindowedDevices.Add(pDevice);
		sDevices.Add(pDevice);
	}
	void GraphicsDeviceAPI::RemoveWindowedDevice(GraphicsDevice* pDevice)
	{
		sWindowedDevices.Remove(pDevice);
		sDevices.Remove(pDevice);
	}
}