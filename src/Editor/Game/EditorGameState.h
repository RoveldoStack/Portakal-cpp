#pragma once
#include <Runtime/Core/Core.h>

namespace Portakal
{
	/// <summary>
	/// Represents the possible states of the editor game modes
	/// </summary>
	enum class PORTAKAL_API EditorGameState
	{
		Idle,
		Running,
		Paused
	};
}