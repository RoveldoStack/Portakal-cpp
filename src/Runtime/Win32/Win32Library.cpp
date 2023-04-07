#include "Win32Library.h"

namespace Portakal
{
	Win32Library::Win32Library(const String& path) : PlatformLibrary(path)
	{
		mLibraryInstance = LoadLibrary(*path);
	}
	Win32Library::~Win32Library()
	{
		if (mLibraryInstance != NULL)
			FreeLibrary(mLibraryInstance);
	}
	void* Win32Library::GetFunction(const String& name)
	{
		if (mLibraryInstance == NULL)
			return nullptr;

		return GetProcAddress(mLibraryInstance,*name);
	}
}