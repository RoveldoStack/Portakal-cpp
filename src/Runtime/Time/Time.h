#pragma once
#include <Runtime/Core/Core.h>

namespace Portakal
{
	class PORTAKAL_API Time
	{
		friend class Application;
	public:
		FORCEINLINE static float GetDeltaTime() { return _deltaTime; }
	private:
		FORCEINLINE static void _SetDeltaTime(const float delta) { _deltaTime = delta; }
	private:
		static float _deltaTime;
	public:
		Time() = delete;
		~Time() = delete;

	};
}