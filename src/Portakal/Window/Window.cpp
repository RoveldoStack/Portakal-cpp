#include "Window.h"

namespace Portakal
{
	Window* Window::CreateWindow(const WindowCreateDesc& desc)
	{
		return nullptr;
	}
	Window::~Window()
	{

	}
	void Window::SetTitle(const std::string& title)
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
}