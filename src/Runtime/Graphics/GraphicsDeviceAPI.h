#pragma once
#include <Runtime/Graphics/StandaloneGraphicsDeviceCreateDesc.h>
#include <Runtime/Graphics/WindowedGraphicsDeviceCreateDesc.h>
#include <Runtime/Containers/Array.h>
#include <Runtime/Graphics/GraphicsDevice.h>

namespace Portakal
{
	class GraphicsDevice;

	/// <summary>
	/// API for graphics devices present in the application
	/// </summary>
	class PORTAKAL_API GraphicsDeviceAPI
	{
		friend class GraphicsModule;
	private:
		static GraphicsDeviceAPI* sAPI;
	public:
		/// <summary>
		/// Returns the default device of the application
		/// </summary>
		/// <returns></returns>
		static GraphicsDevice* GetDefaultDevice();

		/// <summary>
		/// Returns all the available devices
		/// </summary>
		/// <returns></returns>
		/// 
		static Array<GraphicsDevice*> GetDevices();

		/// <summary>
		/// Returns only the standalone devices
		/// </summary>
		/// <returns></returns>
		static Array<GraphicsDevice*> GetStandaloneDevices();

		/// <summary>
		/// Returns only the windowed devices
		/// </summary>
		/// <returns></returns>
		static Array<GraphicsDevice*> GetWindowedDevices();
	private:
		GraphicsDeviceAPI(const Array<GraphicsDevice*>& windowedDevices,const Array<GraphicsDevice*>& standaloneDevices);
		~GraphicsDeviceAPI();
	private:
		Array<GraphicsDevice*> mDevices;
		Array<GraphicsDevice*> mStandaloneDevices;
		Array<GraphicsDevice*> mWindowedDevices;
	};
}