#pragma once
#include <Runtime/Graphics/InputElementDataFormat.h>
#include <Runtime/Graphics/InputElementSemantic.h>
#include <Runtime/Containers/String.h>

namespace Portakal
{
	/// <summary>
	/// Required information to specify a single input element
	/// </summary>
	struct PORTAKAL_API InputElementDesc
	{
		/// <summary>
		/// The name
		/// </summary>
		String Name;

		/// <summary>
		/// The semantic type
		/// </summary>
		InputElementSemantic Semantic;

		/// <summary>
		/// The data format
		/// </summary>
		InputElementDataFormat Format;

		/// <summary>
		/// The offset
		/// </summary>
		unsigned int Offset;
	};
}