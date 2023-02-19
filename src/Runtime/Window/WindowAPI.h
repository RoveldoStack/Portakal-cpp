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
		friend class WindowModule;
	private:
		static WindowAPI* _api;
	public:
		/// <summary>
		/// Returns the defualt window
		/// </summary>
		/// <returns></returns>
		static Window* GetDefaultWindow();

		/// <summary>
		/// Returns the windows
		/// </summary>
		/// <returns></returns>
		static Array<Window*> GetWindows();
	private:
		WindowAPI(const Array<Window*>& windows);
		~WindowAPI();
	private:
		Array<Window*> mWindows;
	};
}