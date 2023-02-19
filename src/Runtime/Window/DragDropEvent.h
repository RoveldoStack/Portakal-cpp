#pragma once
#include <Runtime/Window/WindowEvent.h>

namespace Portakal
{
	/// <summary>
	/// Represents a drag drop into window event
	/// </summary>
	class PORTAKAL_API DragDropEvent : public WindowEvent
	{
	public:
		DragDropEvent(const String& path) : mPath(path) {}
		~DragDropEvent() = default;

		/// <summary>
		/// Returns the dragged file path
		/// </summary>
		/// <returns></returns>
		FORCEINLINE String GetPath() const noexcept { return mPath; }

		FORCEINLINE virtual WindowEventType GetEventType() const noexcept override { return WindowEventType::DragDrop; }
		FORCEINLINE virtual String GetEventMessage() const noexcept { return "File dropped"; }
	private:
		const String mPath;
	};
}