#pragma once
#include <Runtime/Containers/Guid.h>
#include <Runtime/Reflection/Type.h>
#include <Runtime/Math/Vector2.h>
#include <Editor/GUI/Window/EditorWindowDockState.h>

namespace Portakal
{
	class PORTAKAL_API EditorWindow : public Class
	{
		friend class EditorWindowAPI;
		GENERATE_CLASS(EditorWindow);
	public:
		EditorWindow() : mVisible(false),mCloseRequest(false),mParentWindow(nullptr) {}
		virtual ~EditorWindow() = default;

		FORCEINLINE bool HasCloseRequest() const noexcept { return mCloseRequest; }
		FORCEINLINE bool IsVisible() const noexcept { return mVisible; }
		FORCEINLINE Vector2<unsigned int> GetPosition() const noexcept { return mPos; }
		FORCEINLINE Vector2<unsigned int> GetSize() const noexcept { return mSize; }
		FORCEINLINE EditorWindowDockState GetDockState() const noexcept { return mDockState; }

		virtual void OnShow() = 0;
		virtual void OnHide() = 0;
		virtual void OnInitialize() = 0;
		virtual void OnFinalize() = 0;
		virtual void OnPaint() = 0;
	private:
		FORCEINLINE void _SetPosition(const Vector2<unsigned int>& position) { mPos = position; }
		FORCEINLINE void _SetSize(const Vector2<unsigned int>& size) { mSize = size; }
		FORCEINLINE void _SetDockState(const EditorWindowDockState state) { mDockState = state; }
		FORCEINLINE void _SetVisibility(const bool state) { mVisible = state; }
		FORCEINLINE void _SetParentWindow(EditorWindow* pWindow);
	private:
		EditorWindow* mParentWindow;
		Vector2<unsigned int> mPos;
		Vector2<unsigned int> mSize;
		EditorWindowDockState mDockState;
		bool mVisible;
		bool mCloseRequest;
	};

	START_GENERATE_TYPE(EditorWindow);
	START_TYPE_PROPERTIES(EditorWindow);
	END_TYPE_PROPERTIES;
	VIRTUAL_TYPE;
	END_GENERATE_TYPE(EditorWindow);
}