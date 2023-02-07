#include "EditorResourceAPI.h"
#include <Editor/Resource/EditorResource.h>

namespace Portakal
{
	EditorResourceAPI* EditorResourceAPI::sAPI = nullptr;

	EditorResource* EditorResourceAPI::GetResource(const String& name)
	{
		if (sAPI == nullptr)
			return nullptr;

		for (unsigned int i = 0; i < sAPI->mResources.GetCursor(); i++)
		{
			EditorResource* pResource = sAPI->mResources[i];

			if (pResource->GetName() == name)
				return pResource;
		}

		return nullptr;
	}
	EditorResourceAPI::EditorResourceAPI(const Array<EditorResource*>& resources)
	{
		mResources = resources;
		sAPI = this;
	}
	EditorResourceAPI::~EditorResourceAPI()
	{
		sAPI = nullptr;
		for (unsigned int i = 0; i < mResources.GetCursor(); i++)
		{
			delete mResources[i];
		}

		mResources.Clear();
	}
}