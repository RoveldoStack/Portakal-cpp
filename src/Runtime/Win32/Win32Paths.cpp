#include "Win32Paths.h"
#include <Windows.h>
#include <Shlwapi.h>
#include <shellapi.h>
#include <ShlObj_core.h>
namespace Portakal
{
#define SPECIAL_FOLDER_SIZE 512
	String Win32Paths::GetEditorInstallPath()
	{
		char* pBuffer = new char[SPECIAL_FOLDER_SIZE];

		SHGetSpecialFolderPath(NULL, pBuffer, CSIDL_PROGRAM_FILES, false);

		return pBuffer;
	}
}