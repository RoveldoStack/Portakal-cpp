#include "WindowAPI.h"

namespace Portakal
{
	WindowAPI* WindowAPI::_api = nullptr;

	WindowAPI::WindowAPI(const Array<WindowCreateDesc>& descs)
	{
		_api = this;

		for (int i = 0; i < descs.GetCursor(); i++)
		{
			const WindowCreateDesc desc = descs[i];

			_windows.Add(Window::Create(desc));
		}
	}
	WindowAPI::~WindowAPI()
	{
		_api = nullptr;

		for (int i = 0; i < _windows.GetCursor(); i++)
		{
			delete _windows[i];
		}
		_windows.Clear();
	}
	Window* WindowAPI::GetDefaultWindow()
	{
		if (_api == nullptr)
			return nullptr;

		if (_api->_windows.GetCursor() == 0)
			return nullptr;

		return _api->_windows[0];
	}
	Array<Window*> WindowAPI::GetWindows()
	{
		if (_api == nullptr)
			return Array<Window*>();

		return _api->_windows;
	}
}