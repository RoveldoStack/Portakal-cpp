#include "SceneOpenOperation.h"
#include <Editor/Domain/DomainFile.h>
#include <Runtime/Resource/Resource.h>

namespace Portakal
{
	void SceneOpenOperation::OnOpen(DomainFile* pFile)
	{
		pFile->LoadSync();

		Scene* pScene = (Scene*)pFile->GetResource()->GetSubObject();

		pScene->MarkPrimal();
	}
}