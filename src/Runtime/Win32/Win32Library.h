#pragma once
#include <Runtime/Platform/PlatformLibrary.h>
#include <Windows.h>

namespace Portakal
{
	class PORTAKAL_API Win32Library : public PlatformLibrary
	{
	public:
		Win32Library(const String& path);
		virtual ~Win32Library() override;

	private:
		virtual void* GetFunction(const String& name) override;
	private:
		HINSTANCE mLibraryInstance;
	};
}