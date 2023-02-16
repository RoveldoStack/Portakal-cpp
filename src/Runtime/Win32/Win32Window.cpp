#include "Win32Window.h"
#include <Runtime/Assert/Assert.h>
#include <Runtime/Window/WindowEvents.h>
#include <ShlObj_core.h>
#include <Runtime/Input/Keys.h>
#include "Win32Keys.h"

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

                DragAcceptFiles(hwnd, TRUE);
                break;
            }
            case WM_DESTROY:
            {
                DragAcceptFiles(hwnd, FALSE);
                break;
            }
		    case WM_CLOSE:
		    {
			    Win32Window* win32Window = GetUserWindowData(hwnd);

			    win32Window->DispatchWin32Event(new WindowClosedEvent());

			    break;
		    }
		    case WM_MOVE:
		    {
			    Win32Window* win32Window = GetUserWindowData(hwnd);

			    win32Window->DispatchWin32Event(new WindowMovedEvent(LOWORD(lParam), HIWORD(lParam)));
			    break;
		    }
		    case WM_SIZE:
		    {
			    Win32Window* win32Window = GetUserWindowData(hwnd);

			    win32Window->DispatchWin32Event(new WindowResizedEvent(LOWORD(lParam), HIWORD(lParam)));
			    break;
		    }
		    case WM_MOUSEMOVE:
		    {
			    Win32Window* win32Window = GetUserWindowData(hwnd);

			    win32Window->DispatchWin32Event(new MouseMovedEvent(LOWORD(lParam), HIWORD(lParam)));
			    break;
		    }
		    case WM_MOUSEWHEEL:
		    {
			    Win32Window* win32Window = GetUserWindowData(hwnd);

			    win32Window->DispatchWin32Event(new MouseWheelEvent(GET_WHEEL_DELTA_WPARAM(wParam), GET_WHEEL_DELTA_WPARAM(wParam)));
			    break;
		    }
		    case WM_LBUTTONDOWN:
		    {
			    Win32Window* win32Window = GetUserWindowData(hwnd);

			    win32Window->DispatchWin32Event(new MouseButtonDownEvent(0));
			    break;
		    }
		    case WM_LBUTTONUP:
		    {
			    Win32Window* win32Window = GetUserWindowData(hwnd);

			    win32Window->DispatchWin32Event(new MouseButtonUpEvent(0));
			    break;
		    }
		    case WM_RBUTTONDOWN:
		    {
			    Win32Window* win32Window = GetUserWindowData(hwnd);

			    win32Window->DispatchWin32Event(new MouseButtonDownEvent(1));
			    break;
		    }
		    case WM_RBUTTONUP:
		    {
			    Win32Window* win32Window = GetUserWindowData(hwnd);

			    win32Window->DispatchWin32Event(new MouseButtonUpEvent(1));
			    break;
		    }
		    case WM_KEYDOWN:
		    {
			    Win32Window* win32Window = GetUserWindowData(hwnd);

                /*
                * Map win32 vk keys to portakal keys
                */
                const unsigned int key = Win32Keys::GetKey(wParam);

			    win32Window->DispatchWin32Event(new KeyboardKeyDownEvent(key));
			    break;
		    }
		    case WM_KEYUP:
		    {
			    Win32Window* win32Window = GetUserWindowData(hwnd);

                /*
                * Map win32 vk keys to portakal keys
                */
                const unsigned int key = Win32Keys::GetKey(wParam);
               
			    win32Window->DispatchWin32Event(new KeyboardKeyUpEvent(key));

			    break;
		    }
		    case WM_CHAR:
		    {
			    Win32Window* win32Window = GetUserWindowData(hwnd);

			    win32Window->DispatchWin32Event(new KeyboardCharEvent(wParam));
			    break;
		    }
            case WM_DROPFILES:
            {
                Win32Window* pWindow = GetUserWindowData(hwnd);

                TCHAR buffer[MAX_PATH];

                HDROP handle = (HDROP)wParam;

                const unsigned int dropFileCount = DragQueryFile(handle, 0xFFFFFFFF,buffer,MAX_PATH);

                for (unsigned int i = 0; i < dropFileCount; i++)
                {
                    DragQueryFile(handle, i, buffer, MAX_PATH);
                    String str = buffer;
                    pWindow->DispatchWindowEvent(new DragDropEvent(str));

                }

                DragFinish(handle);


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
        wc.style =   CS_HREDRAW | CS_VREDRAW ;
        wc.lpfnWndProc = (WNDPROC)Win32WindowMessageProc;
        wc.cbClsExtra = 0;
        wc.cbWndExtra = sizeof(Win32Window*);
        wc.hInstance = processHandle;
        wc.hCursor = LoadCursor(NULL, IDC_ARROW);
        wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
        wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
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
            WS_OVERLAPPEDWINDOW | WS_EX_ACCEPTFILES,
            desc.PositionX,desc.PositionY,desc.Width,desc.Height,
            NULL,
            NULL,
            processHandle,
            this);

        ASSERT(windowHandle != NULL, "Win32Window", "Failed to create a window");

        mWindowHandle = windowHandle;
        mDeviceContext = GetDC(windowHandle);

        ChangeWindowMessageFilter(WM_DROPFILES, MSGFLT_ADD);
        ChangeWindowMessageFilter(WM_COPYDATA, MSGFLT_ADD);
        ChangeWindowMessageFilter(0x0049, MSGFLT_ADD);
    }
    Win32Window::~Win32Window()
    {
        ReleaseDC(mWindowHandle, mDeviceContext);
        DestroyWindow(mWindowHandle);

        mWindowHandle = NULL;
        mDeviceContext = NULL;
    }

    void Win32Window::DispatchWin32Event(WindowEvent* pEvent)
    {
        DispatchWindowEvent(pEvent);
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