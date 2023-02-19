#pragma once
#include <Runtime/Platform/PlatformFile.h>
#include <Runtime/Platform/PlatformDirectory.h>

namespace Portakal
{
	/// <summary>
	/// Utility class for generating projects
	/// </summary>
	class PORTAKAL_API ProjectGenerator
	{
	public:
		ProjectGenerator() = delete;
		~ProjectGenerator() = delete;

		/// <summary>
		/// Generates project files sync
		/// </summary>
		/// <param name="name"></param>
		/// <param name="folderPath"></param>
		static void GenerateSync(const String& name, const String& folderPath);
	};
}