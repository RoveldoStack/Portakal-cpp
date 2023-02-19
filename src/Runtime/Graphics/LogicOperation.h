#pragma once
#include <Runtime/Core/Core.h>

namespace Portakal
{
	/// <summary>
	/// Available graphics logical operations
	/// </summary>
	enum class PORTAKAL_API LogicOperation
	{
		Clear,
		Set,
		Copy,
		CopyInverted,
		NoOp,
		Invert,
		And,
		NAnd,
		Or,
		NOr,
		XOr,
		Equal,
		AndReverse,
		AndInverted,
		OrReverse,
		OrInverted
	};
}