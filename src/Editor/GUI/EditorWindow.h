#pragma once
#include <Runtime/Containers/Guid.h>
#include <Runtime/Reflection/Type.h>
#include <Runtime/Math/Vector2.h>
#include <Editor/GUI/EditorWindowDockState.h>

namespace Portakal
{
	class PORTAKAL_API EditorWindow : public Class
	{
		GENERATE_CLASS(EditorWindow);
	public:
		EditorWindow() = default;
		virtual ~EditorWindow() = default;

		FORCEINLINE bool IsActive() const noexcept { return _active; }
		FORCEINLINE Vector2<unsigned int> GetPosition() const noexcept { return _position; }
		FORCEINLINE Vector2<unsigned int> GetSize() const noexcept { return _size; }
		FORCEINLINE EditorWindowDockState GetDockState() const noexcept { return _dockState; }

		virtual void OnShow() = 0;
		virtual void OnHide() = 0;
		virtual void OnInitialize() = 0;
		virtual void OnFinalize() = 0;
		virtual void OnPaint() = 0;
	private:
		EditorWindow* _parentWindow;
		Vector2<unsigned int> _position;
		Vector2<unsigned int> _size;
		EditorWindowDockState _dockState;
		bool _visible;
		bool _active;
	};

	START_GENERATE_TYPE(EditorWindow);
	START_TYPE_PROPERTIES(EditorWindow);
	END_TYPE_PROPERTIES;
	VIRTUAL_TYPE;
	END_GENERATE_TYPE(EditorWindow);
}