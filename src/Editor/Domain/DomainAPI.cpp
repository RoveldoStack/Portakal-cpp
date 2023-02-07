#include "DomainAPI.h"
#include <Editor/Domain/DomainFolder.h>

namespace Portakal
{
	DomainAPI* DomainAPI::sAPI = nullptr;

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