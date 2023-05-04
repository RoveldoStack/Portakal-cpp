#include "WindowAPI.h"

namespace Portakal
{
	WindowAPI::WindowAPI()
	{
	}

	WindowAPI::~WindowAPI()
	{

	}

	Window* WindowAPI::GetDefaultWindow()
	{
		if (GetUnderlyingAPI() == nullptr)
			return nullptr;

		if (GetUnderlyingAPI()->mWindows.GetCursor() > 0)
			return GetUnderlyingAPI()->mWindows[0];

		return nullptr;
	}
	Array<Window*> WindowAPI::GetWindows()
	{
		if (GetUnderlyingAPI() == nullptr)
			return {};

		return GetUnderlyingAPI()->mWindows;
	}
	void WindowAPI::RegisterWindow(Window* pWindow)
	{
		if (GetUnderlyingAPI() == nullptr)
			return;

		GetUnderlyingAPI()->mWindows.Add(pWindow);
	}
	void WindowAPI::RemoveWindow(Window* pWindow)
	{
		if (GetUnderlyingAPI() == nullptr)
			return;

		GetUnderlyingAPI()->mWindows.Remove(pWindow);
	}

	
	
}