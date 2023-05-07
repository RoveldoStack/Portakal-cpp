#pragma once
#include <Runtime/Core/Core.h>
#include <Runtime/Reflection/Reflection.h>
namespace Portakal
{
	/// <summary>
	/// Available dock states
	/// </summary>
	PENUM();
	enum class PORTAKAL_API EditorWindowDockState : long long
	{
		None,
		Center,
		Left,
		Right,
		Up,
		Down
	};

#include "EditorWindowDockState.reflect.h"
}