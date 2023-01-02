#include "GraphicsDeviceAPI.h"

namespace Portakal
{
	GraphicsDeviceAPI* GraphicsDeviceAPI::_api = nullptr;

	GraphicsDevice* GraphicsDeviceAPI::GetDefaultDevice()
	{
		if (_api == nullptr)
			return nullptr;

		return _api->_devices.GetCursor() > 0 ? _api->_devices[0] : nullptr;
	}
	Array<GraphicsDevice*> GraphicsDeviceAPI::GetDevices()
	{
		if (_api == nullptr)
			return Array<GraphicsDevice*>();

		return _api->_devices;
	}
	Array<GraphicsDevice*> GraphicsDeviceAPI::GetStandaloneDevices()
	{
		if (_api == nullptr)
			return Array<GraphicsDevice*>();

		return _api->_standaloneDevices;
	}
	Array<GraphicsDevice*> GraphicsDeviceAPI::GetWindowedDevices()
	{
		if (_api == nullptr)
			return Array<GraphicsDevice*>();

		return _api->_windowedDevices;
	}
	GraphicsDeviceAPI::GraphicsDeviceAPI(const Array<GraphicsDevice*>& windowedDevices, const Array<GraphicsDevice*>& standaloneDevices)
	{
		_api = this;

		_api->_standaloneDevices = standaloneDevices;
		_api->_windowedDevices = windowedDevices;
		_api->_devices = windowedDevices;
		_api->_devices.AddRange(standaloneDevices);
	}
	GraphicsDeviceAPI::~GraphicsDeviceAPI()
	{
		_api = nullptr;
	}
}