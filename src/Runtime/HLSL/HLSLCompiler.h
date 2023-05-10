#pragma once
#include <Runtime/Containers/Array.h>
#include <Runtime/Containers/String.h>
#include <Runtime/Graphics/Shader/ShaderStage.h>
#include <Runtime/Memory/ByteBlock.h>
namespace Portakal
{
	class PORTAKAL_API HLSLCompiler
	{
	public:
		static void Compile(const String& source, const String& entryPoint, const ShaderStage stage, const unsigned int major, const unsigned int minor,ByteBlock& bytesOut,String& errorOut);
	public:
		HLSLCompiler() = delete;
		~HLSLCompiler() = delete;
	};
}