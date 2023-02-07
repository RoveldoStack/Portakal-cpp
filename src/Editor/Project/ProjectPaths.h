#pragma once
#include <Runtime/Containers/String.h>

namespace Portakal
{
	class PORTAKAL_API ProjectPaths
	{
		friend class ProjectModule;
	public:
		ProjectPaths() = default;
		~ProjectPaths() = default;

		FORCEINLINE static String GetProjectFolder() { return sProjectFolder; }
		FORCEINLINE static String GetDomainFolder() { return sDomainFolder; }
		FORCEINLINE static String GetSettingsFolder() { return sSettingsFolder; }
	private:
		static String sProjectFolder;
		static String sDomainFolder;
		static String sSettingsFolder;
	};
}