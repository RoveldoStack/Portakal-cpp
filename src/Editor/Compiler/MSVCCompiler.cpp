#include "MSVCCompiler.h"
#include <Runtime/Platform/PlatformProcess.h>
namespace Portakal
{
	bool MSVCCompiler::Compile(const String& compilerPath,const String& projectHandlePath, const CpuArchitecture architecture, const bool bDebug)
	{
		PlatformProcess* pProcess = PlatformProcess::Create(compilerPath, { projectHandlePath,"/Build","configuration/architecture text" });
		pProcess->Start();
		pProcess->WaitForFinish();


		delete pProcess;

		return true;
	}
}