#pragma once
#include <Runtime/Core/Core.h>
#include <Runtime/Containers/Array.h>
#include <Runtime/Input/Gamepad.h>
#include <Runtime/Memory/SharedSafeHeap.h>

namespace Portakal
{
	class PORTAKAL_API InputAPI
	{
		friend class InputModule;
		friend class XInputManager;
	private:
		static InputAPI* sAPI;
	private:
		static void RegisterGamepad(const SharedSafeHeap<Gamepad>& pGamepad);
		static void RemoveGamepad(const SharedSafeHeap<Gamepad>& pGamepad);
	public:
		static Array<SharedSafeHeap<Gamepad>> GetGamepads();
		static SharedSafeHeap<Gamepad> GetDefaultGamepad();
		
	public:

	private:
		InputAPI();
		~InputAPI();

		Array<SharedSafeHeap<Gamepad>> _GetGamepads() const noexcept { return mGamepads; }
		SharedSafeHeap<Gamepad> _GetDefaultGamepad() const noexcept;
		void _RegisterGamepad(const SharedSafeHeap<Gamepad>& pGamepad);
		void _RemoveGamepad(const SharedSafeHeap<Gamepad>& pGamepad);
	private:
		Array<SharedSafeHeap<Gamepad>> mGamepads;
	};
}