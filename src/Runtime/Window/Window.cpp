#include "Window.h"
#include <Runtime/Window/WindowEvent.h>

#ifdef PORTAKAL_OS_WINDOWS
#include <Runtime/Win32/Win32Window.h>
typedef Portakal::Win32Window PlatformAbstraction;
#endif
#include <Runtime/Log/Log.h>

namespace Portakal
{
	Window* Window::Create(const WindowCreateDesc& desc)
	{
		return new PlatformAbstraction(desc);
	}
	Window::~Window()
	{

	}
	void Window::Show()
	{
		ShowCore();
	}
	void Window::Hide()
	{
		HideCore();
	}
	void Window::SetTitle(const String& title)
	{
		SetTitle(title);

		_title = title;
	}
	void Window::SetSize(const unsigned int width, const unsigned int height)
	{
		SetSizeCore(width, height);

		_width = width;
		_height = height;
	}

	void Window::SetPosition(const unsigned int x, const unsigned int y)
	{
		SetPositionCore(x, y);

		_positionX = x;
		_positionY = y;
	}
	void Window::PollEvents()
	{
		/*
		* Delete events
		*/
		for (int i = 0; i < _polledEvents.GetCursor(); i++)
		{
			delete _polledEvents[i];
		}

		/*
		* Clear the list
		*/
		_polledEvents.Clear();

		PollEventsCore();
	}
	void Window::DispatchWindowEvent(WindowEvent* pEvent)
	{
		_polledEvents.Add(pEvent);
	}
}