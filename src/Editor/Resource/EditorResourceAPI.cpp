#include "EditorResourceAPI.h"
#include <Editor/Resource/EditorResource.h>

namespace Portakal
{
	EditorResource* EditorResourceAPI::GetResource(const String& name)
	{
		EditorResourceAPI* pAPI = GetUnderlyingAPI();
		if (pAPI == nullptr)
			return nullptr;

		for (unsigned int i = 0; i < pAPI->mResources.GetCursor(); i++)
		{
			EditorResource* pResource = pAPI->mResources[i];

			if (pResource->GetName() == name)
				return pResource;
		}

		return nullptr;
	}
	void EditorResourceAPI::ClearResources()
	{
		EditorResourceAPI* pAPI = GetUnderlyingAPI();
		if (pAPI == nullptr)
			return;

		for (unsigned int i = 0; i < pAPI->mResources.GetCursor(); i++)
		{
			delete pAPI->mResources[i];
		}

		pAPI->mResources.Clear();
	}

	EditorResourceAPI::EditorResourceAPI(const Array<EditorResource*>& loadedResources)
	{
		mResources = loadedResources;
	}
	EditorResourceAPI::~EditorResourceAPI()
	{
	}
}