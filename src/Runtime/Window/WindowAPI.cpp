#include "WindowAPI.h"

namespace Portakal
{
	Array<Window*> WindowAPI::sWindows;

	Window* WindowAPI::GetDefaultWindow()
	{
		if (sWindows.GetCursor() > 0)
			return sWindows[0];

		return nullptr;
	}
	Array<Window*> WindowAPI::GetWindows()
	{
		return sWindows;
	}
	void WindowAPI::RegisterWindow(Window* pWindow)
	{
		sWindows.Add(pWindow);
	}
	void WindowAPI::RemoveWindow(Window* pWindow)
	{
		sWindows.Remove(pWindow);
	}
}