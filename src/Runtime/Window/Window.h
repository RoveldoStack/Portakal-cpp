#pragma once
#include <Runtime/Window/WindowCreateDesc.h>
#include <Runtime/Containers/Array.h>

namespace Portakal
{
	class GraphicsDevice;
	class WindowEvent;

	/// <summary>
	/// Represents a OS window
	/// </summary>
	class PORTAKAL_API Window
	{
	public:
		static Window* Create(const WindowCreateDesc& desc);

		virtual ~Window();

		FORCEINLINE GraphicsDevice* GetChildDevice() const noexcept { return _childDevice; }
		FORCEINLINE String GetTitle() const noexcept { return _title; }
		FORCEINLINE unsigned int GetWidth() const noexcept { return _width; }
		FORCEINLINE unsigned int GetHeight() const noexcept { return _height; }
		FORCEINLINE unsigned int GetPositionX() const noexcept { return _positionX; }
		FORCEINLINE unsigned int GetPositionY() const noexcept { return _positionY; }
		FORCEINLINE Array<WindowEvent*> GetPolledEvents() const noexcept { return _polledEvents; }
		FORCEINLINE bool IsActive() const noexcept { return _active; }
		FORCEINLINE bool IsVisible() const noexcept { return _visible; }

		void Show();
		void Hide();
		void SetTitle(const String& title);
		void SetSize(const unsigned int width, const unsigned int height);
		void SetPosition(const unsigned int x, const unsigned int y);
		void PollEvents();

	protected:
		Window(const WindowCreateDesc& desc) : _title(desc.Name),_width(desc.Width),_height(desc.Height),_positionX(desc.PositionX),_positionY(desc.PositionY),_childDevice(nullptr),_active(true),_visible(false) {}

		void DispatchWindowEvent(WindowEvent* pEvent);
		virtual void ShowCore() = 0;
		virtual void HideCore() = 0;
		virtual void SetTitleCore(const String& title) = 0;
		virtual void SetSizeCore(const unsigned int width, const unsigned int height) = 0;
		virtual void SetPositionCore(const unsigned int x, const unsigned int y) = 0;
		virtual void PollEventsCore() = 0;
	private:
		void OnWindowMoved(const unsigned int x,const unsigned int y);
		void OnWindowResized(unsigned int width, const unsigned int height);
		void OnWindowClosed();
	private:
		Array<WindowEvent*> _polledEvents;
		GraphicsDevice* _childDevice;
		String _title;
		unsigned int _width;
		unsigned int _height;
		unsigned int _positionX;
		unsigned int _positionY;
		bool _active;
		bool _visible;
	};
}