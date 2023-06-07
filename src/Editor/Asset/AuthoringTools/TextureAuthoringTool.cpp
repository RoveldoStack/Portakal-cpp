#include "TextureAuthoringTool.h"
#include <Libs/ImGui/imgui.h>
#include <Editor/Resource/EditorImageResource.h>
#include <Runtime/Resource/Texture/TextureResource.h>
#include <Editor/Domain/DomainFile.h>
#include <Runtime/Graphics/Resource/ResourceTable.h>
#include <Runtime/Math/Vector2F.h>
#include <Runtime/Math/Math.h>
#include <Editor/Renderer/ImGuiAPI.h>
#include <Editor/Renderer/ImGuiTextureBinding.h>
#include <Editor/Renderer/ImGuiRenderer.h>
#include <Runtime/Resource/Resource.h>

namespace Portakal
{
	void TextureAuthoringTool::OnInitialize()
	{

	}
	void TextureAuthoringTool::OnPaint(DomainFile* pFile)
	{
		if (!pFile->IsLoaded())
			pFile->LoadSync();

		TextureResource* pTexture = (TextureResource*)pFile->GetResource()->PeekSubObject();
		if (pTexture == nullptr)
		{
			return;
		}

		const float targetSize = 512;
		const float minDimension = Math::Max(pTexture->GetWidth(), pTexture->GetHeight());
		const float multiplier = targetSize / minDimension;
		const Vector2F dimension = { pTexture->GetWidth() * multiplier,pTexture->GetHeight() * multiplier };

		ImGui::Text("Texture auth tool");
		ImGuiTextureBinding* pBinding = ImGuiAPI::GetDefaultRenderer()->GetOrCreateTextureBinding(pTexture);
		ImGui::Image(pBinding, {dimension.X,dimension.Y});

	}
	void TextureAuthoringTool::OnFinalize()
	{
	}
}