#pragma once
#include <Runtime/Core/Core.h>

namespace Portakal
{
	/// <summary>
	/// Available dock states
	/// </summary>
	enum class PORTAKAL_API EditorWindowDockState : unsigned int
	{
		None = 0,
		Center = 1,
		Left = 2,
		Right = 3,
		Up = 4,
		Down = 5
	};
}