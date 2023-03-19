#pragma once
#include <Runtime/Core/Core.h>
#include <Runtime/Containers/Array.h>
#include <Runtime/Window/Window.h>

namespace Portakal
{
	/// <summary>
	/// API for making the windows visible across the application
	/// </summary>
	class PORTAKAL_API WindowAPI
	{
	public:
		FORCEINLINE static Window* GetDefaultWindow();
		FORCEINLINE static Array<Window*> GetWindows();
		static void RegisterWindow(Window* pWindow);
		static void RemoveWindow(Window* pWindow);
	private:
		static Array<Window*> sWindows;
	private:
		WindowAPI() = delete;
		~WindowAPI() = delete;
	};
}