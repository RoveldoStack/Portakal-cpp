#pragma once
#include <Runtime/Window/WindowCreateDesc.h>
#include <Runtime/Containers/Array.h>
#include <Runtime/Event/Event.h>

namespace Portakal
{
	class GraphicsDevice;
	class WindowEvent;

	/// <summary>
	/// Represents a platform agnostic window
	/// </summary>
	class PORTAKAL_API Window
	{
		friend class WindowChildDeviceAdapter;
	public:
		/// <summary>
		/// Creates anew window
		/// </summary>
		/// <param name="desc"></param>
		/// <returns></returns>
		static Window* Create(const WindowCreateDesc& desc);

		virtual ~Window();

		/// <summary>
		/// Returns the child graphics device (if any)
		/// </summary>
		/// <returns></returns>
		FORCEINLINE GraphicsDevice* GetChildDevice() const noexcept { return mChildDevice; }

		/// <summary>
		/// Returns the title
		/// </summary>
		/// <returns></returns>
		FORCEINLINE String GetTitle() const noexcept { return mTitle; }

		/// <summary>
		/// Returns the width
		/// </summary>
		/// <returns></returns>
		FORCEINLINE unsigned int GetWidth() const noexcept { return mWidth; }

		/// <summary>
		/// Returns the height
		/// </summary>
		/// <returns></returns>
		FORCEINLINE unsigned int GetHeight() const noexcept { return mHeight; }

		/// <summary>
		/// Returns the offset-x
		/// </summary>
		/// <returns></returns>
		FORCEINLINE unsigned int GetPositionX() const noexcept { return mPosX; }

		/// <summary>
		/// Returns the offset-y
		/// </summary>
		/// <returns></returns>
		FORCEINLINE unsigned int GetPositionY() const noexcept { return mPosY; }

		/// <summary>
		/// Returns the polled events
		/// </summary>
		/// <returns></returns>
		FORCEINLINE Array<WindowEvent*> GetPolledEvents() const noexcept { return mPolledEvents; }

		/// <summary>
		/// Returns whether its active or not
		/// </summary>
		/// <returns></returns>
		FORCEINLINE bool IsActive() const noexcept { return mActive; }

		/// <summary>
		/// Returns whether its visible or not
		/// </summary>
		/// <returns></returns>
		FORCEINLINE bool IsVisible() const noexcept { return mVisible; }

		/// <summary>
		/// Makes the window visible
		/// </summary>
		void Show();

		/// <summary>
		/// Makes the window invisible
		/// </summary>
		void Hide();

		/// <summary>
		/// Sets the title of the window
		/// </summary>
		/// <param name="title"></param>
		void SetTitle(const String& title);

		/// <summary>
		/// Sets the size of the window
		/// </summary>
		/// <param name="width"></param>
		/// <param name="height"></param>
		void SetSize(const unsigned int width, const unsigned int height);

		/// <summary>
		/// Sets the position of the window
		/// </summary>
		/// <param name="x"></param>
		/// <param name="y"></param>
		void SetPosition(const unsigned int x, const unsigned int y);

		/// <summary>
		/// Polls the queued events
		/// </summary>
		void PollEvents();

		/// <summary>
		/// Registers anew event listener
		/// </summary>
		/// <param name="listenerPtr"></param>
		void RegisterEventListener(Delegate<void,const WindowEvent*> listenerPtr);

		/// <summary>
		/// Removes an existing event listener
		/// </summary>
		/// <param name="listenerPtr"></param>
		void RemoveEventListener(Delegate<void,const WindowEvent*> listenerPtr);

	protected:
		Window(const WindowCreateDesc& desc) : mTitle(desc.Name), mWidth(desc.Width), mHeight(desc.Height), mPosX(desc.PositionX), mPosY(desc.PositionY),mChildDevice(nullptr), mActive(true), mVisible(false) {}

		/// <summary>
		/// Used for dispatching events to the listeners
		/// </summary>
		/// <param name="pEvent"></param>
		void DispatchWindowEvent(WindowEvent* pEvent);

		virtual void ShowCore() = 0;
		virtual void HideCore() = 0;
		virtual void SetTitleCore(const String& title) = 0;
		virtual void SetSizeCore(const unsigned int width, const unsigned int height) = 0;
		virtual void SetPositionCore(const unsigned int x, const unsigned int y) = 0;
		virtual void PollEventsCore() = 0;
	private:

		/// <summary>
		/// Called when window is moved
		/// </summary>
		/// <param name="x"></param>
		/// <param name="y"></param>
		void OnWindowMoved(const unsigned int x,const unsigned int y);

		/// <summary>
		/// Called when window is resized
		/// </summary>
		/// <param name="width"></param>
		/// <param name="height"></param>
		void OnWindowResized(unsigned int width, const unsigned int height);

		/// <summary>
		/// Called when window is closed
		/// </summary>
		void OnWindowClosed();

		/// <summary>
		/// Intenral child device setter
		/// </summary>
		/// <param name="pDevice"></param>
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