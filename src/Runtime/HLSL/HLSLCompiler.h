#pragma once
#include <Runtime/Containers/Array.h>
#include <Runtime/Containers/String.h>
#include <Runtime/Graphics/Shader/ShaderStage.h>
#include <Runtime/Memory/ByteBlock.h>
namespace Portakal
{
	/*
	* Simple HLSL Compiler util class
	*/
	class PORTAKAL_API HLSLCompiler
	{
	public:
		/// <summary>
		/// Compiles the given shader description into a byteblock. This returns DXIL.
		/// </summary>
		/// <param name="source"></param>
		/// <param name="entryPoint"></param>
		/// <param name="stage"></param>
		/// <param name="major"></param>
		/// <param name="minor"></param>
		/// <param name="bytesOut"></param>
		/// <param name="errorOut"></param>
		static void Compile(const String& source, const String& entryPoint, const ShaderStage stage, const unsigned int major, const unsigned int minor,ByteBlock& bytesOut,String& errorOut);
	public:
		HLSLCompiler() = delete;
		~HLSLCompiler() = delete;
	};
}