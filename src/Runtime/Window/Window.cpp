#include "Window.h"
#include <Runtime/Window/WindowEvent.h>
#include <Runtime/Window/WindowEvents.h>
#include <Runtime/Graphics/GraphicsDevice.h>
#include <Runtime/Graphics/SwapchainFramebuffer.h>

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

		_visible = true;
	}
	void Window::Hide()
	{
		HideCore();

		_visible = false;
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
		WindowEventType eventType = pEvent->GetEventType();

		switch (eventType)
		{
			case Portakal::WindowEventType::WindowClosed:
			{
				OnWindowClosed();
				break;
			}
			case Portakal::WindowEventType::WindowMoved:
			{
				const WindowMovedEvent* pEventData = (const WindowMovedEvent*)pEvent;
				OnWindowMoved(pEventData->GetX(), pEventData->GetY());
				break;
			}
			case Portakal::WindowEventType::WindowResized:
			{
				const WindowResizedEvent* pEventData = (const WindowResizedEvent*)pEvent;
				OnWindowResized(pEventData->GetWidth(), pEventData->GetHeight());
				break;
			}
			case Portakal::WindowEventType::KeyboardDown:
				break;
			case Portakal::WindowEventType::KeyboardUp:
				break;
			case Portakal::WindowEventType::Char:
				break;
			case Portakal::WindowEventType::MouseButtonDown:
				break;
			case Portakal::WindowEventType::MouseButtonUp:
				break;
			case Portakal::WindowEventType::MouseMoved:
				break;
			case Portakal::WindowEventType::MouseScrolled:
				break;
			default:
				break;
		}
		_polledEvents.Add(pEvent);
	}
	void Window::OnWindowMoved(const unsigned int x, const unsigned int y)
	{
		_positionX = x;
		_positionY = y;
	}
	void Window::OnWindowResized(unsigned int width, const unsigned int height)
	{
		_width = width;
		_height = height;

		if (_childDevice != nullptr)
			((SwapchainFramebuffer*)_childDevice->GetSwapchainFramebuffer())->_Resize(width, height);
	}
	void Window::OnWindowClosed()
	{
		_active = false;
	}
}