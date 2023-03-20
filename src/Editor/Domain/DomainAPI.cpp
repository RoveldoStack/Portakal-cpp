#include "DomainAPI.h"
#include <Editor/Domain/DomainFolder.h>
#include <Editor/Domain/DomainFile.h>
#include <Runtime/Log/Log.h>

namespace Portakal
{
	DomainAPI* DomainAPI::sAPI = nullptr;

	DomainFolder* DomainAPI::GetRootFolder()
	{
		if (sAPI == nullptr)
			return nullptr;

		return sAPI->mRootFolder;
	}

	DomainFile* GetFileViaIDRecursive(DomainFolder* pFolder, const Guid& id)
	{
		const Array<DomainFile*> files = pFolder->GetFiles();
		for (unsigned int i = 0; i < files.GetCursor(); i++)
		{
			DomainFile* pFile = files[i];
			LOG("D", "Target: %s, current: %s", *(Guid::ToString(id)), *(Guid::ToString(pFile->GetID())));
			if (pFile->GetID() == id)
				return pFile;
		}

		const Array<DomainFolder*> folders = pFolder->GetSubFolders();
		for (unsigned int i = 0; i < folders.GetCursor(); i++)
		{
			DomainFile* pFile = GetFileViaIDRecursive(folders[i], id);
			if (pFile != nullptr)
				return pFile;
		}

		return nullptr;
	}
	DomainFile* DomainAPI::GetFileViaID(const Guid& id)
	{
		if (sAPI == nullptr)
			return nullptr;

		return GetFileViaIDRecursive(sAPI->mRootFolder, id);
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