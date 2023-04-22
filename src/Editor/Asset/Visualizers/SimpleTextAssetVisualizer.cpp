#include "SimpleTextAssetVisualizer.h"
#include <Editor/Resource/EditorImageResource.h>
#include <Libs/ImGui/imgui.h>
#include <Editor/Resource/EditorResourceAPI.h>
#include <Runtime/Resource/Texture/TextureResource.h>
#include <Runtime/Graphics/Resource/ResourceTable.h>

namespace Portakal
{
	SimpleTextAssetVisualizer::SimpleTextAssetVisualizer()
	{
		mResource = (EditorImageResource*)EditorResourceAPI::GetResource("TextIcon.png");
	}
	SimpleTextAssetVisualizer::~SimpleTextAssetVisualizer()
	{
		mResource = nullptr;
	}
	TextureResource* SimpleTextAssetVisualizer::OnPaint(DomainFile* pFile)
	{
		if (mResource == nullptr)
			return nullptr;

		return mResource->GetTexture();
	}
}