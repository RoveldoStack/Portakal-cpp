#pragma once
#include <Runtime/Core/Core.h>

namespace Portakal
{
	/// <summary>
	/// Available gpu comparision methods
	/// </summary>
	enum class PORTAKAL_API ComparisionMethod
	{
        Never,
        Less,
        Equal,
        LessEqual,
        Greater,
        NotEqual,
        GreaterEqual,
        Always
	};
}