#pragma once
#include <Runtime/Window/Window.h>
#include <Windows.h>

namespace Portakal
{
	class PORTAKAL_API Win32Window : public Window
	{
	private:
		static LRESULT CALLBACK Win32WindowMessageProc(HWND hwnd,UINT uMsg,WPARAM wParam,LPARAM lParam);
	public:
		Win32Window(const WindowCreateDesc& desc);
		virtual ~Win32Window() override;

		FORCEINLINE HWND GetWin32WindowHandle() const noexcept { return _windowHandle; }
		FORCEINLINE HDC GetWin32WindowDeviceContext() const noexcept { return _windowDeviceContext;; }
	private:
		virtual void ShowCore() override;
		virtual void HideCore() override;
		virtual void SetTitleCore(const String& title) override;
		virtual void SetSizeCore(const unsigned int width, const unsigned int height) override;
		virtual void SetPositionCore(const unsigned int x, const unsigned int y) override;
		virtual void PollEventsCore() override;
	private:
		HWND _windowHandle;
		HDC _windowDeviceContext;

	};
}