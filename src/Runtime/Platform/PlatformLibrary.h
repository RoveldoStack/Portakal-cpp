#pragma once
#include <Runtime/Containers/String.h>

namespace Portakal
{
	class PORTAKAL_API PlatformLibrary
	{
	public:
		static PlatformLibrary* Create(const String& path);

	public:
		FORCEINLINE String GetPath() const noexcept { return mPath; }
		FORCEINLINE virtual void* GetFunction(const String& name) = 0;
	protected:
		PlatformLibrary(const String& path) : mPath(path){}
		virtual ~PlatformLibrary() = 0 {};
	private:
		const String mPath;
	};
}