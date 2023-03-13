#include "SceneAssetVisualizer.h"
#include <Editor/Domain/DomainFile.h>
#include <Runtime/Resource/Resource.h>
#include <Editor/Resource/EditorImageResource.h>
#include <Editor/Resource/EditorResourceAPI.h>

namespace Portakal
{
	TextureResource* SceneAssetVisualizer::OnPaint(DomainFile* pFile)
	{
		return ((EditorImageResource*)EditorResourceAPI::GetResource("SceneIcon.png"))->GetTexture();
	}
}