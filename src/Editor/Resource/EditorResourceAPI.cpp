#include "EditorResourceAPI.h"
#include <Editor/Resource/EditorResource.h>

namespace Portakal
{
	Array<EditorResource*> EditorResourceAPI::sResources;

	EditorResource* EditorResourceAPI::GetResource(const String& name)
	{
		for (unsigned int i = 0; i < sResources.GetCursor(); i++)
		{
			EditorResource* pResource = sResources[i];

			if (pResource->GetName() == name)
				return pResource;
		}

		return nullptr;
	}
	void EditorResourceAPI::ClearResources()
	{
		for (unsigned int i = 0; i < sResources.GetCursor(); i++)
		{
			delete sResources[i];
		}

		sResources.Clear();
	}
}