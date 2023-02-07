#pragma once
#include <Runtime/Window/WindowCreateDesc.h>
#include <Runtime/Containers/Array.h>
#include <Runtime/Event/Event.h>

namespace Portakal
{
	class GraphicsDevice;
	class WindowEvent;

	/// <summary>
	/// Represents a OS window
	/// </summary>
	class PORTAKAL_API Window
	{
		friend class WindowChildDeviceAdapter;
	public:
		static Window* Create(const WindowCreateDesc& desc);

		virtual ~Window();

		FORCEINLINE GraphicsDevice* GetChildDevice() const noexcept { return mChildDevice; }
		FORCEINLINE String GetTitle() const noexcept { return mTitle; }
		FORCEINLINE unsigned int GetWidth() const noexcept { return mWidth; }
		FORCEINLINE unsigned int GetHeight() const noexcept { return mHeight; }
		FORCEINLINE unsigned int GetPositionX() const noexcept { return mPosX; }
		FORCEINLINE unsigned int GetPositionY() const noexcept { return mPosY; }
		FORCEINLINE Array<WindowEvent*> GetPolledEvents() const noexcept { return mPolledEvents; }
		FORCEINLINE bool IsActive() const noexcept { return mActive; }
		FORCEINLINE bool IsVisible() const noexcept { return mVisible; }

		void Show();
		void Hide();
		void SetTitle(const String& title);
		void SetSize(const unsigned int width, const unsigned int height);
		void SetPosition(const unsigned int x, const unsigned int y);
		void PollEvents();
		void RegisterEventListener(Delegate<void,const WindowEvent*> listenerPtr);
		void RemoveEventListener(Delegate<void,const WindowEvent*> listenerPtr);

	protected:
		Window(const WindowCreateDesc& desc) : mTitle(desc.Name), mWidth(desc.Width), mHeight(desc.Height), mPosX(desc.PositionX), mPosY(desc.PositionY),mChildDevice(nullptr), mActive(true), mVisible(false) {}

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
		void _SetChildDevice(GraphicsDevice* pDevice) { mChildDevice = pDevice; }
	private:
		Event<void,const WindowEvent*> mEventFeed;
		Array<WindowEvent*> mPolledEvents;
		GraphicsDevice* mChildDevice;
		String mTitle;
		unsigned int mWidth;
		unsigned int mHeight;
		unsigned int mPosX;
		unsigned int mPosY;
		bool mActive;
		bool mVisible;
	};
}