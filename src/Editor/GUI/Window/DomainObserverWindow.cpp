#include "DomainObserverWindow.h"
#include <Libs/ImGui/imgui.h>
#include <Editor/Domain/DomainAPI.h>
#include <Editor/Domain/DomainFolder.h>
#include <Runtime/Platform/PlatformMessage.h>
#include <Runtime/Resource/Texture/TextureResource.h>
#include <Runtime/DX12/DX12ResourceTable.h>
#include <Editor/Resource/EditorImageResource.h>
#include <Editor/Resource/EditorResourceAPI.h>
#include <Runtime/Event/Event.h>
#include <Runtime/Window/WindowEvent.h>
#include <Runtime/Window/WindowAPI.h>
#include <Runtime/Message/MessageAPI.h>
#include <Runtime/Log/Log.h>

namespace Portakal
{
	void DomainObserverWindow::OnEvent(const WindowEvent* pEvent)
	{

	}

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

		Window* pTargetWindow = WindowAPI::GetDefaultWindow();
		if (pTargetWindow == nullptr)
		{
			MessageAPI::BroadcastMessage("Window missing, unable to register for event feed");
			return;
		}

		pTargetWindow->RegisterEventListener(GENERATE_MEMBER_DELEGATE(this, DomainObserverWindow::OnEvent, void, const WindowEvent*));
	}

	void DomainObserverWindow::OnFinalize()
	{
		Window* pTargetWindow = WindowAPI::GetDefaultWindow();
		if (pTargetWindow == nullptr)
		{
			MessageAPI::BroadcastMessage("Window missing, unable to unregister for event feed");
			return;
		}
		pTargetWindow->RemoveEventListener(GENERATE_MEMBER_DELEGATE(this, DomainObserverWindow::OnEvent, void, const WindowEvent*));
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