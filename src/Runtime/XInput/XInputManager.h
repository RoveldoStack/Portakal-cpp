#pragma once
#include <Runtime/Core/Core.h>

namespace Portakal
{
	class Window;
	class PORTAKAL_API XInputManager
	{
	public:
		XInputManager() = delete;
		~XInputManager() = delete;

		static void Initialize();
		static void CollectGamepadInputStates(Window* pWindow);

	};
}