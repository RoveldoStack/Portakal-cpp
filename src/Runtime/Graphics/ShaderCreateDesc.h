#pragma once
#include <Runtime/Graphics/ShaderStage.h>
#include <Runtime/Containers/String.h>

namespace Portakal
{
	/// <summary>
	/// Required information to create a shader
	/// </summary>
	struct PORTAKAL_API ShaderCreateDesc
	{
		/// <summary>
		/// The target stage
		/// </summary>
		ShaderStage Stage;

		/// <summary>
		/// The entry point method name
		/// </summary>
		String EntryPointMethod;

		/// <summary>
		/// The source of text
		/// </summary>
		String Source;
	};
}