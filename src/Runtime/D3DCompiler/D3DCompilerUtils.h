#pragma once
#include <Runtime/Containers/String.h>
#include <Runtime/Graphics/ShaderStage.h>

namespace Portakal
{
	/// <summary>
	/// D3D compiler utility class
	/// </summary>
	class PORTAKAL_API D3DCompilerUtils
	{
	public:
		D3DCompilerUtils() = delete;
		~D3DCompilerUtils() = delete;

		/// <summary>
		/// Returns the compiler target string eg. "vs_5_0","ps_5_5"
		/// </summary>
		/// <param name="stage"></param>
		/// <param name="major"></param>
		/// <param name="minor"></param>
		/// <returns></returns>
		FORCEINLINE static String GetCompilerTarget(const ShaderStage stage, const unsigned int major, const unsigned int minor);
	};
}