#include "SceneOpenOperation.h"
#include <Editor/Domain/DomainFile.h>
#include <Runtime/Resource/Resource.h>

namespace Portakal
{
	void SceneOpenOperation::OnOpen(DomainFile* pFile)
	{
		pFile->LoadSync();

		//SharedHeap<Scene> pScene = pFile->GetResource()->GetSubObject();
		SharedHeap<Scene> pScene = pFile->GetResource()->GetSubObject();

		pScene->MarkPrimal();
	}
}