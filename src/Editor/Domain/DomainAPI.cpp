#include "DomainAPI.h"
#include <Editor/Domain/DomainFolder.h>

namespace Portakal
{
	DomainAPI* DomainAPI::sAPI = nullptr;

	DomainFolder* DomainAPI::GetRootFolder()
	{
		if (sAPI == nullptr)
			return nullptr;

		return sAPI->mRootFolder;
	}

	DomainAPI::DomainAPI(const String& domainFolderPath) : mFolderPath(domainFolderPath)
	{
		mRootFolder = new DomainFolder(nullptr, domainFolderPath);
		sAPI = this;
	}
	DomainAPI::~DomainAPI()
	{
		sAPI = nullptr;
	}
}