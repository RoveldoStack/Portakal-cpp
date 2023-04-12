#pragma once
#include <Runtime/Core/Core.h>
#include <Runtime/Containers/Array.h>
#include <Runtime/Input/Gamepad.h>
#include <Runtime/Memory/SharedSafeHeap.h>

namespace Portakal
{
	/// <summary>
	/// An input API for the whole application
	/// </summary>
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
		/// <summary>
		/// Returns the active gamepads
		/// </summary>
		/// <returns></returns>
		static Array<SharedSafeHeap<Gamepad>> GetGamepads();

		/// <summary>
		/// Returns the default(first) gamepad connected to the system
		/// </summary>
		/// <returns></returns>
		static SharedSafeHeap<Gamepad> GetDefaultGamepad();
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