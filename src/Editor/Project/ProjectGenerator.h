#pragma once
#include <Runtime/Platform/PlatformFile.h>
#include <Runtime/Platform/PlatformDirectory.h>

namespace Portakal
{
	class PORTAKAL_API ProjectGenerator
	{
	public:
		ProjectGenerator() = delete;
		~ProjectGenerator() = delete;


		static void GenerateSync(const String& name, const String& folderPath);
	};
}