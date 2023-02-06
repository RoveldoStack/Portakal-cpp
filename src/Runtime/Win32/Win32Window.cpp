#include "Win32Window.h"
#include <Runtime/Assert/Assert.h>
#include <Runtime/Window/WindowEvents.h>

namespace Portakal
{
    Win32Window* GetUserWindowData(HWND windowHandle)
    {
        return (Win32Window*)GetWindowLongPtr(windowHandle, -21);
    }
    LRESULT Win32Window::Win32WindowMessageProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        switch (uMsg)
        {
        case WM_CREATE:
        {
            Win32Window* pWindow = (Win32Window*)((LPCREATESTRUCT)lParam)->lpCreateParams;

            SetWindowLongPtr(hwnd, -21, (LONG_PTR)pWindow);

            break;
        }
		case WM_CLOSE:
		{
			Win32Window* win32Window = GetUserWindowData(hwnd);

			win32Window->DispatchWindowEvent(new WindowClosedEvent());

			break;
		}
		case WM_MOVE:
		{
			Win32Window* win32Window = GetUserWindowData(hwnd);

			win32Window->DispatchWindowEvent(new WindowMovedEvent(LOWORD(lParam), HIWORD(lParam)));
			break;
		}
		case WM_SIZE:
		{
			Win32Window* win32Window = GetUserWindowData(hwnd);

			win32Window->DispatchWindowEvent(new WindowResizedEvent(LOWORD(lParam), HIWORD(lParam)));
			break;
		}
		case WM_MOUSEMOVE:
		{
			Win32Window* win32Window = GetUserWindowData(hwnd);

			win32Window->DispatchWindowEvent(new MouseMovedEvent(LOWORD(lParam), HIWORD(lParam)));
			break;
		}
		case WM_MOUSEWHEEL:
		{
			Win32Window* win32Window = GetUserWindowData(hwnd);

			win32Window->DispatchWindowEvent(new MouseWheelEvent(GET_WHEEL_DELTA_WPARAM(wParam), GET_WHEEL_DELTA_WPARAM(wParam)));
			break;
		}
		case WM_LBUTTONDOWN:
		{
			Win32Window* win32Window = GetUserWindowData(hwnd);

			win32Window->DispatchWindowEvent(new MouseButtonDownEvent(0));
			break;
		}
		case WM_LBUTTONUP:
		{
			Win32Window* win32Window = GetUserWindowData(hwnd);

			win32Window->DispatchWindowEvent(new MouseButtonUpEvent(0));
			break;
		}
		case WM_RBUTTONDOWN:
		{
			Win32Window* win32Window = GetUserWindowData(hwnd);

			win32Window->DispatchWindowEvent(new MouseButtonDownEvent(1));
			break;
		}
		case WM_RBUTTONUP:
		{
			Win32Window* win32Window = GetUserWindowData(hwnd);

			win32Window->DispatchWindowEvent(new MouseButtonUpEvent(1));
			break;
		}
		case WM_KEYDOWN:
		{
			Win32Window* win32Window = GetUserWindowData(hwnd);

			win32Window->DispatchWindowEvent(new KeyboardKeyDownEvent(wParam));
			break;
		}
		case WM_KEYUP:
		{
			Win32Window* win32Window = GetUserWindowData(hwnd);

			win32Window->DispatchWindowEvent(new KeyboardKeyUpEvent(wParam));

			break;
		}
		case WM_CHAR:
		{
			Win32Window* win32Window = GetUserWindowData(hwnd);

			win32Window->DispatchWindowEvent(new KeyboardCharEvent(wParam));
			break;
		}
        default:
            break;
        }
        return DefWindowProc(hwnd,uMsg,wParam,lParam);
    }
    Win32Window::Win32Window(const WindowCreateDesc& desc) : Window(desc)
    {
        constexpr char WINDOW_CLASS_NAME[] = "Win32WindowClassName";

        HINSTANCE processHandle = GetModuleHandle(0);

        /*
        * Create win32 class
        */
        WNDCLASSEX wc = { 0 };
        wc.cbSize = sizeof(WNDCLASSEX);
        wc.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
        wc.lpfnWndProc = (WNDPROC)Win32WindowMessageProc;
        wc.cbClsExtra = 0;
        wc.cbWndExtra = sizeof(Win32Window*);
        wc.hInstance = processHandle;
        wc.hCursor = 0;
        wc.hIcon = LoadIcon(NULL, IDI_HAND);
        wc.hbrBackground = NULL;
        wc.lpszMenuName = NULL;
        wc.lpszClassName = WINDOW_CLASS_NAME;
        wc.hIconSm = NULL;

        ASSERT(RegisterClassEx(&wc) != NULL, "Win32Window", "Window class registration failed!");

        /*
        * Create window handle
        */
        HWND windowHandle = CreateWindowEx(
            0,
            WINDOW_CLASS_NAME,
            *desc.Name,
            WS_OVERLAPPEDWINDOW,
            desc.PositionX,desc.PositionY,desc.Width,desc.Height,
            NULL,
            NULL,
            processHandle,
            this);

        ASSERT(windowHandle != NULL, "Win32Window", "Failed to create a window");

        mWindowHandle = windowHandle;
        mDeviceContext = GetDC(windowHandle);
    }
    Win32Window::~Win32Window()
    {
        ReleaseDC(mWindowHandle, mDeviceContext);
        DestroyWindow(mWindowHandle);

        mWindowHandle = NULL;
        mDeviceContext = NULL;
    }

    void Win32Window::ShowCore()
    {
        ShowWindow(mWindowHandle, SW_SHOW);
    }
    void Win32Window::HideCore()
    {
        ShowWindow(mWindowHandle, SW_HIDE);
    }
    void Win32Window::SetTitleCore(const String& title)
    {
        SetWindowText(mWindowHandle,*title);
    }
    void Win32Window::SetSizeCore(const unsigned int width, const unsigned int height)
    {
        SetWindowPos(mWindowHandle, NULL, GetPositionX(), GetPositionY(), width, height,0);
    }
    void Win32Window::SetPositionCore(const unsigned int x, const unsigned int y)
    {
        SetWindowPos(mWindowHandle, NULL, x, y, GetWidth(), GetHeight(),0);
    }
    void Win32Window::PollEventsCore()
    {
        MSG msg = { 0 };
        while (PeekMessage(&msg, mWindowHandle, 0, 0, PM_REMOVE) > 0)
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
}