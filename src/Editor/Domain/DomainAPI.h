#pragma once
#include <Runtime/Core/Core.h>
#include <Runtime/Containers/String.h>

namespace Portakal
{
	class DomainFolder;
	class PORTAKAL_API DomainAPI
	{
		friend class DomainModule;
	private:
		static DomainAPI* sAPI;
	public:

	private:
		DomainAPI(const String& domainFolderPath);
		~DomainAPI();
	private:
		DomainFolder* mRootFolder;
		const String mFolderPath;
	};
}