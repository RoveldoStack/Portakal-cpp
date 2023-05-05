#pragma once
#include <Runtime/Core/Core.h>
#include <Runtime/Containers/Array.h>
#include <Runtime/Input/Gamepad.h>
#include <Runtime/Memory/SharedSafeHeap.h>
#include <Runtime/Object/API.h>

namespace Portakal
{
	/// <summary>
	/// An input API for the whole application
	/// </summary>
	class PORTAKAL_API InputAPI : public API<InputAPI>
	{
		friend class InputModule;
		friend class XInputManager;
	private:
		static void RegisterGamepad(Gamepad* pGamepad);
		static void RemoveGamepad(Gamepad* pGamepad);
	public:
		/// <summary>
		/// Returns the active gamepads
		/// </summary>
		/// <returns></returns>
		static Array<Gamepad*> GetGamepads();

		/// <summary>
		/// Returns the default(first) gamepad connected to the system
		/// </summary>
		/// <returns></returns>
		static Gamepad* GetDefaultGamepad();
	public:
		InputAPI();
		virtual ~InputAPI() override;
	private:
		Array<Gamepad*> mGamepads;
	};
}