#include "ShaderAssetVisualizer.h"
#include <Editor/Domain/DomainFile.h>
#include <Runtime/Resource/Texture/TextureResource.h>
#include <Editor/Resource/EditorResourceAPI.h>
#include <Editor/Resource/EditorImageResource.h>
#include <Runtime/Resource/Resource.h>
#include <memory>

namespace Portakal
{
	TextureResource* ShaderAssetVisualizer::OnPaint(DomainFile* pFile)
	{
		return ((EditorImageResource*)EditorResourceAPI::GetResource("ShaderIcon.png"))->GetTexture();
	}
}