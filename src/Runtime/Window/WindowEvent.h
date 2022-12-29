#pragma once
#include <Runtime/Containers/String.h>
#include <Runtime/Window/WindowEventType.h>

namespace Portakal
{
	class PORTAKAL_API WindowEvent
	{
	public:
		~WindowEvent() = default;

		FORCEINLINE virtual WindowEventType GetEventType() const noexcept = 0;
		FORCEINLINE virtual String GetEventMessage() const noexcept = 0;

		FORCEINLINE bool IsHandled() const noexcept { return _handled; }

		void MarkHandled() { _handled = true; }

	protected:
		WindowEvent() : _handled(false) {}
	private:
		bool _handled;
	};
}