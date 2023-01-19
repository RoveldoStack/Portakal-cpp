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
		EditorWindow() : _visible(false),_hasCloseRequest(false),_parentWindow(nullptr) {}
		virtual ~EditorWindow() = default;

		FORCEINLINE bool HasCloseRequest() const noexcept { return _hasCloseRequest; }
		FORCEINLINE bool IsVisible() const noexcept { return _visible; }
		FORCEINLINE Vector2<unsigned int> GetPosition() const noexcept { return _position; }
		FORCEINLINE Vector2<unsigned int> GetSize() const noexcept { return _size; }
		FORCEINLINE EditorWindowDockState GetDockState() const noexcept { return _dockState; }

		virtual void OnShow() = 0;
		virtual void OnHide() = 0;
		virtual void OnInitialize() = 0;
		virtual void OnFinalize() = 0;
		virtual void OnPaint() = 0;
	private:
		FORCEINLINE void _SetPosition(const Vector2<unsigned int>& position) { _position = position; }
		FORCEINLINE void _SetSize(const Vector2<unsigned int>& size) { _size = size; }
		FORCEINLINE void _SetDockState(const EditorWindowDockState state) { _dockState = state; }
		FORCEINLINE void _SetVisibility(const bool state) { _visible = state; }
		FORCEINLINE void _SetParentWindow(EditorWindow* pWindow);
	private:
		EditorWindow* _parentWindow;
		Vector2<unsigned int> _position;
		Vector2<unsigned int> _size;
		EditorWindowDockState _dockState;
		bool _visible;
		bool _hasCloseRequest;
	};

	START_GENERATE_TYPE(EditorWindow);
	START_TYPE_PROPERTIES(EditorWindow);
	END_TYPE_PROPERTIES;
	VIRTUAL_TYPE;
	END_GENERATE_TYPE(EditorWindow);
}