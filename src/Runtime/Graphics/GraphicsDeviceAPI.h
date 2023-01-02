#pragma once
#include <Runtime/Graphics/StandaloneGraphicsDeviceCreateDesc.h>
#include <Runtime/Graphics/WindowedGraphicsDeviceCreateDesc.h>
#include <Runtime/Containers/Array.h>


namespace Portakal
{
	class GraphicsDevice;
	class PORTAKAL_API GraphicsDeviceAPI
	{
		friend class GraphicsDeviceModule;
	private:
		static GraphicsDeviceAPI* _api;
	public:
		static GraphicsDevice* GetDefaultDevice();
		static Array<GraphicsDevice*> GetDevices();
		static Array<GraphicsDevice*> GetStandaloneDevices();
		static Array<GraphicsDevice*> GetWindowedDevices();
	private:
		GraphicsDeviceAPI(const Array<GraphicsDevice*>& windowedDevices,const Array<GraphicsDevice*>& standaloneDevices);
		~GraphicsDeviceAPI();
	private:
		Array<GraphicsDevice*> _devices;
		Array<GraphicsDevice*> _standaloneDevices;
		Array<GraphicsDevice*> _windowedDevices;
	};
}