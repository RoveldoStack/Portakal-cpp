#include "DomainObserverWindow.h"
#include <Libs/ImGui/imgui.h>
#include <Editor/Domain/DomainAPI.h>
#include <Editor/Domain/DomainFolder.h>
#include <Runtime/Platform/PlatformMessage.h>
#include <Runtime/Resource/Texture/TextureResource.h>
#include <Runtime/DX12/DX12ResourceTable.h>
#include <Editor/Resource/EditorImageResource.h>
#include <Editor/Resource/EditorResourceAPI.h>
namespace Portakal
{

	void DomainObserverWindow::OnShow()
	{

	}
	void DomainObserverWindow::OnHide()
	{

	}
	void DomainObserverWindow::OnInitialize()
	{
		mCurrentFolder = DomainAPI::GetRootFolder();
		if (mCurrentFolder == nullptr)
		{
			PlatformMessage::ShowMessageBox("Domain Observer Window", "Domain root folder missing!");
			return;
		}
	}
	void DomainObserverWindow::OnFinalize()
	{

	}
	void DomainObserverWindow::OnPaint()
	{
		if (mCurrentFolder == nullptr)
			return;

		ImGui::Text(*mCurrentFolder->GetFolderPath());
		ImGui::Separator();
		ImGui::Spacing();

		//ImGui::Image(pTex->GetTexture()->GetIsolatedResourceTable()->GetHandle(), {128,128});
	}
}