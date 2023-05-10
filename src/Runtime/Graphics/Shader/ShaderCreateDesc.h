#pragma once
#include <Runtime/Graphics/Shader/ShaderStage.h>
#include <Runtime/Containers/String.h>
#include <Runtime/Memory/ByteBlock.h>

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
		/// Bytes of the compiled source
		/// </summary>
		ByteBlock Bytes;
	};
}