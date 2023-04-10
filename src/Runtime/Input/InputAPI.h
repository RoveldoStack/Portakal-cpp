#pragma once
#include <Runtime/Core/Core.h>
#include <Runtime/Containers/Array.h>
#include <Runtime/Input/Gamepad.h>

namespace Portakal
{
	class PORTAKAL_API InputAPI
	{
		friend class InputModule;
		friend class XInputManager;
	private:
		static InputAPI* sAPI;
	private:
		static void RegisterGamepad(Gamepad* pGamepad);
		static void RemoveGamepad(Gamepad* pGamepad);
	public:
		static Array<Gamepad*> GetGamepads();
		static Gamepad* GetDefaultGamepad();
		
	public:

	private:
		InputAPI();
		~InputAPI();

		Array<Gamepad*> _GetGamepads() const noexcept { return mGamepads; }
		Gamepad* _GetDefaultGamepad() const noexcept { if (mGamepads.GetCursor() > 0) { return mGamepads[0]; } return nullptr; }
		void _RegisterGamepad(Gamepad* pGamepad) { mGamepads.Add(pGamepad); }
		void _RemoveGamepad(Gamepad* pGamepad) { mGamepads.Remove(pGamepad); }
	private:
		Array<Gamepad*> mGamepads;
	};
}