#pragma once
#include <Runtime/Core/Core.h>
#include <Runtime/Containers/Array.h>
#include <Runtime/Window/Window.h>

namespace Portakal
{
	class PORTAKAL_API WindowAPI
	{
	private:
		static WindowAPI* _api;
	public:
		WindowAPI(const Array<WindowCreateDesc>& descs);
		~WindowAPI();

		static Window* GetDefaultWindow();
		static Array<Window*> GetWindows();
	private:
		Array<Window*> _windows;
	};
}