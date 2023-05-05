#include "GraphicsDeviceAPI.h"

namespace Portakal
{
	GraphicsDevice* GraphicsDeviceAPI::GetDefaultDevice()
	{
		GraphicsDeviceAPI* pAPI = GetUnderlyingAPI();
		if (pAPI == nullptr)
			return nullptr;
		


		if (pAPI->mWindowedDevices.GetCursor() > 0)
			return pAPI->mWindowedDevices[0];
		if (pAPI->mStandaloneDevices.GetCursor() > 0)
			return pAPI->mStandaloneDevices[0];

		return nullptr;
	}
	GraphicsDevice* GraphicsDeviceAPI::GetDefaultWindowedDevice()
	{
		GraphicsDeviceAPI* pAPI = GetUnderlyingAPI();
		if (pAPI == nullptr)
			return nullptr;

		if (pAPI->mWindowedDevices.GetCursor() > 0)
			return pAPI->mWindowedDevices[0];

		return nullptr;
	}
	GraphicsDevice* GraphicsDeviceAPI::GetDefaultStandaloneDevice()
	{
		GraphicsDeviceAPI* pAPI = GetUnderlyingAPI();

		if (pAPI->mStandaloneDevices.GetCursor() > 0)
			return pAPI->mStandaloneDevices[0];

		return nullptr;
	}
	Array<GraphicsDevice*> GraphicsDeviceAPI::GetAllDevices()
	{
		GraphicsDeviceAPI* pAPI = GetUnderlyingAPI();
		if (pAPI == nullptr)
			return {};

		return pAPI->mDevices;
	}
	Array<GraphicsDevice*> GraphicsDeviceAPI::GetWindowedDevices()
	{
		GraphicsDeviceAPI* pAPI = GetUnderlyingAPI();
		if (pAPI == nullptr)
			return {};

		return pAPI->mWindowedDevices;
	}
	Array<GraphicsDevice*> GraphicsDeviceAPI::GetStandaloneDevices()
	{
		GraphicsDeviceAPI* pAPI = GetUnderlyingAPI();
		if (pAPI == nullptr)
			return {};

		return pAPI->mStandaloneDevices;
	}
	void GraphicsDeviceAPI::RegisterStandaloneDevice(GraphicsDevice* pDevice)
	{
		GraphicsDeviceAPI* pAPI = GetUnderlyingAPI();
		if (pAPI == nullptr)
			return;

		pAPI->mStandaloneDevices.Add(pDevice);
		pAPI->mDevices.Add(pDevice);
	}
	void GraphicsDeviceAPI::RemoveStandaloneDevice(GraphicsDevice* pDevice)
	{
		GraphicsDeviceAPI* pAPI = GetUnderlyingAPI();
		if (pAPI == nullptr)
			return;

		pAPI->mStandaloneDevices.Remove(pDevice);
		pAPI->mDevices.Remove(pDevice);
	}
	void GraphicsDeviceAPI::RegisterWindowedDevice(GraphicsDevice* pDevice)
	{
		GraphicsDeviceAPI* pAPI = GetUnderlyingAPI();
		if (pAPI == nullptr)
			return;

		pAPI->mWindowedDevices.Add(pDevice);
		pAPI->mDevices.Add(pDevice);
	}
	void GraphicsDeviceAPI::RemoveWindowedDevice(GraphicsDevice* pDevice)
	{
		GraphicsDeviceAPI* pAPI = GetUnderlyingAPI();
		if (pAPI == nullptr)
			return;

		pAPI->mWindowedDevices.Remove(pDevice);
		pAPI->mDevices.Remove(pDevice);
	}
	GraphicsDeviceAPI::GraphicsDeviceAPI()
	{

	}
	GraphicsDeviceAPI::~GraphicsDeviceAPI()
	{

	}
}