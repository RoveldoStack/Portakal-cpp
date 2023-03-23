#include "Compiler.h"

#ifdef PORTAKAL_OS_WINDOWS
#include <Editor/Compiler/MSVCCompiler.h>
typedef Portakal::MSVCCompiler PlatformAbstraction;
#endif
#include <Runtime/Message/MessageAPI.h>
namespace Portakal
{
	void Compiler::Compile(const String& compilerPath,const String& projectHandlePath, const CpuArchitecture architecture, const bool bDebug)
	{
		if (!PlatformAbstraction::Compile(compilerPath,projectHandlePath, architecture, bDebug))
		{
			MessageAPI::BroadcastMessage("Failed to compile the target project");
		}
	}
}