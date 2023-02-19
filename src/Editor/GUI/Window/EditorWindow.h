#pragma once
#include <Runtime/Containers/Guid.h>
#include <Runtime/Reflection/Type.h>
#include <Runtime/Math/Vector2.h>
#include <Editor/GUI/Window/EditorWindowDockState.h>

namespace Portakal
{
	/// <summary>
	/// Represents an editor window
	/// </summary>
	class PORTAKAL_API EditorWindow : public Class
	{
		friend class EditorWindowAPI;
		GENERATE_CLASS(EditorWindow);
	public:
		EditorWindow() : mVisible(false),mCloseRequest(false),mParentWindow(nullptr),mID(Guid::Create()) {}
		virtual ~EditorWindow() = default;

		/// <summary>
		/// Returns whether this window has a close request
		/// </summary>
		/// <returns></returns>
		FORCEINLINE bool HasCloseRequest() const noexcept { return mCloseRequest; }

		/// <summary>
		/// Returns whether is window is visible or not
		/// </summary>
		/// <returns></returns>
		FORCEINLINE bool IsVisible() const noexcept { return mVisible; }

		/// <summary>
		/// Returns the window position
		/// </summary>
		/// <returns></returns>
		FORCEINLINE Vector2<unsigned int> GetPosition() const noexcept { return mPos; }

		/// <summary>
		/// Returns the window size
		/// </summary>
		/// <returns></returns>
		FORCEINLINE Vector2<unsigned int> GetSize() const noexcept { return mSize; }

		/// <summary>
		/// Returns the dock state
		/// </summary>
		/// <returns></returns>
		FORCEINLINE EditorWindowDockState GetDockState() const noexcept { return mDockState; }

		/// <summary>
		/// Returns the id 
		/// </summary>
		/// <returns></returns>
		FORCEINLINE Guid GetID() const noexcept { return mID; }

		/// <summary>
		/// Called when transitioned from invisible to visible
		/// </summary>
		virtual void OnShow() = 0;

		/// <summary>
		/// Called when transitioned from visible to invisible
		/// </summary>
		virtual void OnHide() = 0;

		/// <summary>
		/// Called upon intialization
		/// </summary>
		virtual void OnInitialize() = 0;

		/// <summary>
		/// Called upon finalization
		/// </summary>
		virtual void OnFinalize() = 0;

		/// <summary>
		/// Called upon every frame from the renderer
		/// </summary>
		virtual void OnPaint() = 0;
	private:
		/// <summary>
		/// Internal setter for position
		/// </summary>
		/// <param name="position"></param>
		FORCEINLINE void _SetPosition(const Vector2<unsigned int>& position) { mPos = position; }

		/// <summary>
		/// Internal setter for size
		/// </summary>
		/// <param name="size"></param>
		FORCEINLINE void _SetSize(const Vector2<unsigned int>& size) { mSize = size; }

		/// <summary>
		/// Internal setter for dock state
		/// </summary>
		/// <param name="state"></param>
		FORCEINLINE void _SetDockState(const EditorWindowDockState state) { mDockState = state; }

		/// <summary>
		/// Internal setter for visibility
		/// </summary>
		/// <param name="state"></param>
		FORCEINLINE void _SetVisibility(const bool state) { mVisible = state; }

		/// <summary>
		/// Internal setter for parent window
		/// </summary>
		/// <param name="pWindow"></param>
		FORCEINLINE void _SetParentWindow(EditorWindow* pWindow);
	private:
		EditorWindow* mParentWindow;
		Vector2<unsigned int> mPos;
		Vector2<unsigned int> mSize;
		EditorWindowDockState mDockState;
		Guid mID;
		bool mVisible;
		bool mCloseRequest;
	};

	START_GENERATE_TYPE(EditorWindow);
	START_TYPE_PROPERTIES(EditorWindow);
	END_TYPE_PROPERTIES;
	NO_DEFAULT_CONSTRUCTOR;
	END_GENERATE_TYPE(EditorWindow);
}