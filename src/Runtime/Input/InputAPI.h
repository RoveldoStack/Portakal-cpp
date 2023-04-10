#pragma once
#include <Runtime/Core/Core.h>
#include <Runtime/Containers/Array.h>
#include <Runtime/Input/IGamepad.h>

namespace Portakal
{
	class PORTAKAL_API InputAPI
	{
		friend class InputModule;
	private:
		static InputAPI* sAPI;
	public:
		static Array<IGamepad*> GetGamepads();
		static IGamepad* GetDefaultGamepad();
		static void RegisterGamepad(IGamepad* pGamepad);
		static void RemoveGamepad(IGamepad* pGamepad);
	public:

	private:
		InputAPI();
		~InputAPI();
	private:
		Array<IGamepad*> mGamepads;
	};
}