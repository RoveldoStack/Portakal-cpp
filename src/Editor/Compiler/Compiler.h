#pragma once
#include <Runtime/Containers/String.h>
#include <Editor/Compiler/CpuArchitecture.h>

namespace Portakal
{
	class PORTAKAL_API Compiler
	{
	public:
		static void Compile(const String& compilerPath,const String& projectHandlePath,const CpuArchitecture architecture,const bool bDebug);
	public:
		Compiler() = delete;
		~Compiler() = delete;

	};
}