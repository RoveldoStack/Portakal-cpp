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
	public:
		FORCEINLINE static GraphicsDevice* GetDefaultDevice();
		FORCEINLINE static GraphicsDevice* GetDefaultWindowedDevice();
		FORCEINLINE static GraphicsDevice* GetDefaultStandaloneDevice();
		FORCEINLINE static Array<GraphicsDevice*> GetAllDevices();
		FORCEINLINE static Array<GraphicsDevice*> GetWindowedDevices();
		FORCEINLINE static Array<GraphicsDevice*> GetStandaloneDevices();

		static void RegisterStandaloneDevice(GraphicsDevice* pDevice);
		static void RemoveStandaloneDevice(GraphicsDevice* pDevice);
		static void RegisterWindowedDevice(GraphicsDevice* pDevice);
		static void RemoveWindowedDevice(GraphicsDevice* pDevice);
	private:
		static Array<GraphicsDevice*> sDevices;
		static Array<GraphicsDevice*> sStandaloneDevices;
		static Array<GraphicsDevice*> sWindowedDevices;
	public:
		GraphicsDeviceAPI() = delete;
		~GraphicsDeviceAPI() = delete;
	
	};
}