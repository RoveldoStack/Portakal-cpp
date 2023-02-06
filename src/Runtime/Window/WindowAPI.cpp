#include "WindowAPI.h"

namespace Portakal
{
	WindowAPI* WindowAPI::_api = nullptr;

	WindowAPI::WindowAPI(const Array<Window*>& windows)
	{
		mWindows = windows;
		_api = this;
	}
	WindowAPI::~WindowAPI()
	{
		_api = nullptr;

		mWindows.Clear();
	}
	Window* WindowAPI::GetDefaultWindow()
	{
		if (_api == nullptr)
			return nullptr;

		if (_api->mWindows.GetCursor() == 0)
			return nullptr;

		return _api->mWindows[0];
	}
	Array<Window*> WindowAPI::GetWindows()
	{
		if (_api == nullptr)
			return Array<Window*>();

		return _api->mWindows;
	}
}