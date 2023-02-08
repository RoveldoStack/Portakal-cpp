#pragma once
#include <Runtime/Window/WindowEvent.h>

namespace Portakal
{
	class PORTAKAL_API DragDropEvent : public WindowEvent
	{
	public:
		DragDropEvent(const String& path) : mPath(path) {}
		~DragDropEvent() = default;

		FORCEINLINE String GetPath() const noexcept { return mPath; }

		FORCEINLINE virtual WindowEventType GetEventType() const noexcept override { return WindowEventType::DragDrop; }
		FORCEINLINE virtual String GetEventMessage() const noexcept { return "File dropped"; }
	private:
		const String mPath;
	};
}