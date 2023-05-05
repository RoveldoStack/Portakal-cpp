#pragma once
#include <Runtime/Graphics/StandaloneGraphicsDeviceCreateDesc.h>
#include <Runtime/Graphics/WindowedGraphicsDeviceCreateDesc.h>
#include <Runtime/Containers/Array.h>
#include <Runtime/Graphics/GraphicsDevice.h>
#include <Runtime/Object/API.h>

namespace Portakal
{
	class GraphicsDevice;

	/// <summary>
	/// API for graphics devices present in the application
	/// </summary>
	class PORTAKAL_API GraphicsDeviceAPI : public API<GraphicsDeviceAPI>
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
		Array<GraphicsDevice*> mDevices;
		Array<GraphicsDevice*> mStandaloneDevices;
		Array<GraphicsDevice*> mWindowedDevices;
	public:
		GraphicsDeviceAPI();
		virtual ~GraphicsDeviceAPI() override;
	
	};
}