#pragma once
#include <Runtime/Containers/String.h>
#include <Editor/Compiler/CpuArchitecture.h>

namespace Portakal
{
	class PORTAKAL_API MSVCCompiler
	{
	public:
		static bool Compile(const String& compilerPath,const String& projectHandlePath, const CpuArchitecture architecture, const bool bDebug);
	public:
		MSVCCompiler() = delete;
		~MSVCCompiler() = delete;
	};
}