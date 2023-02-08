#include "SimpleTextAssetVisualizer.h"
#include <Editor/Resource/EditorImageResource.h>
#include <Libs/ImGui/imgui.h>
#include <Editor/Resource/EditorResourceAPI.h>
#include <Runtime/Resource/Texture/TextureResource.h>
#include <Runtime/Graphics/ResourceTable.h>

namespace Portakal
{
	SimpleTextAssetVisualizer::SimpleTextAssetVisualizer()
	{
		mResource = (EditorImageResource*)EditorResourceAPI::GetResource("ShaderIcon.png");
	}
	SimpleTextAssetVisualizer::~SimpleTextAssetVisualizer()
	{
		mResource = nullptr;
	}
	TextureResource* SimpleTextAssetVisualizer::OnPaint(const DomainFile* pFile)
	{
		if (mResource == nullptr)
			return nullptr;

		return mResource->GetTexture();
	}
}