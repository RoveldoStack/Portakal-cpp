#pragma once
#include <Runtime/Core/Core.h>

namespace Portakal
{
	/// <summary>
	/// Existing gamepad buttons
	/// </summary>
	enum class PORTAKAL_API GamepadButtons : unsigned int
	{
		A,
		B,
		X,
		Y,
		DPadLeft,
		DPadRight,
		DPadUp,
		DPadDown,
		ShouldLeft,
		ShouldRight,
		ThumbLeft,
		ThumRight,
		Back,
		Start,
		COUNT
	};
}