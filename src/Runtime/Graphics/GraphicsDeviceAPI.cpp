#include "GraphicsDeviceAPI.h"

namespace Portakal
{
	GraphicsDeviceAPI* GraphicsDeviceAPI::sAPI = nullptr;

	GraphicsDevice* GraphicsDeviceAPI::GetDefaultDevice()
	{
		if (sAPI == nullptr)
			return nullptr;

		return sAPI->mDevices.GetCursor() > 0 ? sAPI->mDevices[0] : nullptr;
	}
	Array<GraphicsDevice*> GraphicsDeviceAPI::GetDevices()
	{
		if (sAPI == nullptr)
			return Array<GraphicsDevice*>();

		return sAPI->mDevices;
	}
	Array<GraphicsDevice*> GraphicsDeviceAPI::GetStandaloneDevices()
	{
		if (sAPI == nullptr)
			return Array<GraphicsDevice*>();

		return sAPI->mStandaloneDevices;
	}
	Array<GraphicsDevice*> GraphicsDeviceAPI::GetWindowedDevices()
	{
		if (sAPI == nullptr)
			return Array<GraphicsDevice*>();

		return sAPI->mWindowedDevices;
	}
	GraphicsDeviceAPI::GraphicsDeviceAPI(const Array<GraphicsDevice*>& windowedDevices, const Array<GraphicsDevice*>& standaloneDevices)
	{
		sAPI = this;

		sAPI->mStandaloneDevices = standaloneDevices;
		sAPI->mWindowedDevices = windowedDevices;
		sAPI->mDevices = windowedDevices;
		sAPI->mDevices.AddRange(standaloneDevices);
	}
	GraphicsDeviceAPI::~GraphicsDeviceAPI()
	{
		sAPI = nullptr;
	}
}