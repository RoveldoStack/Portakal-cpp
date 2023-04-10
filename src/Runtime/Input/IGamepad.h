#pragma once
#include <Runtime/Core/Core.h>

namespace Portakal
{
	class PORTAKAL_API IGamepad
	{
	public:
		IGamepad() = default;
		~IGamepad() = default;

		void SetVibration(const float amount);
	private:

	};
}