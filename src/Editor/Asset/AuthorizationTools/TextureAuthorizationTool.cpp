#include "TextureAuthorizationTool.h"
#include <Libs/ImGui/imgui.h>
#include <Editor/Resource/EditorImageResource.h>
#include <Runtime/Resource/Texture/TextureResource.h>
#include <Editor/Domain/DomainFile.h>
#include <Runtime/Graphics/ResourceTable.h>

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
		ImGui::Text("Texture auth tool");
		ImGui::Image(pTexture->GetIsolatedResourceTable()->GetHandle(), {512,512});

	}
	void TextureAuthorizationTool::OnFinalize()
	{
	}
}