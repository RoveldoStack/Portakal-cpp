#include "TextureAuthorizationTool.h"
#include <Libs/ImGui/imgui.h>
#include <Editor/Resource/EditorImageResource.h>
#include <Runtime/Resource/Texture/TextureResource.h>
#include <Editor/Domain/DomainFile.h>
#include <Runtime/Graphics/ResourceTable.h>
#include <Runtime/Math/Vector2.h>
#include <Runtime/Math/Math.h>
namespace Portakal
{
	void TextureAuthorizationTool::OnInitialize()
	{

	}
	void TextureAuthorizationTool::OnPaint(DomainFile* pFile)
	{
		if (!pFile->IsLoaded())
			pFile->LoadSync();

		TextureResource* pTexture = (TextureResource*)pFile->GetLoadedSubObject();
		if (pTexture == nullptr)
		{
			return;
		}

		const float targetSize = 512;
		const float minDimension = Math::Max(pTexture->GetWidth(), pTexture->GetHeight());
		const float multiplier = targetSize / minDimension;
		const Vector2F dimension = { pTexture->GetWidth() * multiplier,pTexture->GetHeight() * multiplier };

		ImGui::Text("Texture auth tool");
		ImGui::Image(pTexture->GetIsolatedResourceTable()->GetHandle(), { dimension.X,dimension.Y});

	}
	void TextureAuthorizationTool::OnFinalize()
	{
	}
}