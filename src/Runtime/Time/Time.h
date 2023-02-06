#pragma once
#include <Runtime/Core/Core.h>

namespace Portakal
{
	class PORTAKAL_API Time
	{
		friend class Application;
	public:
		FORCEINLINE static float GetDeltaTime() { return mDeltaTime; }
	private:
		FORCEINLINE static void _SetDeltaTime(const float delta) { mDeltaTime = delta; }
	private:
		static float mDeltaTime;
	public:
		Time() = delete;
		~Time() = delete;

	};
}