#include "Window.h"
#include <Runtime/Window/WindowEvent.h>
#include <Runtime/Window/WindowEvents.h>
#include <Runtime/Graphics/GraphicsDevice.h>
#include <Runtime/Graphics/Swapchain.h>

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

		mVisible = true;
	}
	void Window::Hide()
	{
		HideCore();

		mVisible = false;
	}
	void Window::SetTitle(const String& title)
	{
		SetTitle(title);

		mTitle = title;
	}
	void Window::SetSize(const unsigned int width, const unsigned int height)
	{
		SetSizeCore(width, height);

		mWidth = width;
		mHeight = height;
	}

	void Window::SetPosition(const unsigned int x, const unsigned int y)
	{
		SetPositionCore(x, y);

		mPosX = x;
		mPosY = y;
	}
	void Window::PollEvents()
	{
		/*
		* Delete events
		*/
		for (int i = 0; i < mPolledEvents.GetCursor(); i++)
		{
			delete mPolledEvents[i];
		}

		/*
		* Clear the list
		*/
		mPolledEvents.Clear();

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
		mPolledEvents.Add(pEvent);
	}
	void Window::OnWindowMoved(const unsigned int x, const unsigned int y)
	{
		mPosX = x;
		mPosY = y;
	}
	void Window::OnWindowResized(unsigned int width, const unsigned int height)
	{
		mWidth = width;
		mHeight = height;

		if (mChildDevice != nullptr)
		{
			mChildDevice->GetSwapchain()->Resize(width, height);
		}
	}
	void Window::OnWindowClosed()
	{
		mActive = false;
	}
}