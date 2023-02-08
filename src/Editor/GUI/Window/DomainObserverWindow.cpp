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
#include <Runtime/Window/DragDropEvent.h>
#include <Runtime/Platform/PlatformDirectory.h>
#include <Runtime/Platform/PlatformFile.h>
#include <Editor/Asset/TextAssetSerializer.h>
#include <Editor/Domain/DomainFile.h>
#include <Editor/Asset/IAssetVisualizer.h>
#include <Runtime/Assert/Assert.h>

namespace Portakal
{
	void DomainObserverWindow::OnEvent(const WindowEvent* pEvent)
	{
		if (pEvent->GetEventType() == WindowEventType::DragDrop)
		{
			const DragDropEvent* pDrop = (const DragDropEvent*)pEvent;
			const String path = pDrop->GetPath();

			if (PlatformDirectory::IsDirectoryExist(path))
			{
				OnFolderDrop(path);
			}
			else if (PlatformFile::IsExist(path))
			{
				OnFileDrop(path);
			}
			else // invalid
			{

			}
		}
	}

	void DomainObserverWindow::OnShow()
	{

	}

	void DomainObserverWindow::OnHide()
	{

	}

	void DomainObserverWindow::OnInitialize()
	{
		/*
		* Validate current folder
		*/
		mCurrentFolder = DomainAPI::GetRootFolder();
		if (mCurrentFolder == nullptr)
		{
			PlatformMessage::ShowMessageBox("Domain Observer Window", "Domain root folder missing!");
			return;
		}

		/*
		* Register this window to window event feed
		*/
		Window* pTargetWindow = WindowAPI::GetDefaultWindow();
		if (pTargetWindow == nullptr)
		{
			MessageAPI::BroadcastMessage("Window missing, unable to register for event feed");
			return;
		}

		pTargetWindow->RegisterEventListener(GENERATE_MEMBER_DELEGATE(this, DomainObserverWindow::OnEvent, void, const WindowEvent*));

		/*
		* Load icons
		*/
		mInvalidIcon = (EditorImageResource*)EditorResourceAPI::GetResource("InvalidIcon.png");
		mFolderIcon = (EditorImageResource*)EditorResourceAPI::GetResource("FolderIcon.png");

		/*
		* Validate ICONS
		*/
		ASSERT(mInvalidIcon != nullptr, "DomainObserverWindow", "Unable to find invalid icon!");
		ASSERT(mFolderIcon != nullptr, "DomainobserverWindow", "Unable to find folder icon");

		/*
		* Set defaults
		*/
		mItemSize = { 64,64 };
		mItemGap = { 12,12 };
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
		/*
		* Validate current folder
		*/
		if (mCurrentFolder == nullptr)
			return;

		/*
		* Draw header
		*/
		ImGui::Text(*mCurrentFolder->GetFolderPath());
		ImGui::Separator();
		ImGui::Spacing();

		/*
		* Draw folders
		*/
		const Array<DomainFolder*> folders = mCurrentFolder->GetSubFolders();
		const ImVec2 availableSpace = ImGui::GetContentRegionAvail();
		ImVec2 startPosition = ImGui::GetCursorPos();
		ImVec2 currentCursorPosition = startPosition;
		for (unsigned int i = 0; i < folders.GetCursor(); i++)
		{
			DomainFolder* pFolder = folders[i];

			ImGui::SetCursorPos(currentCursorPosition);
			ImGui::Image(mFolderIcon->GetTexture()->GetIsolatedResourceTable()->GetHandle(), { mItemSize.X,mItemSize.Y });

			if (currentCursorPosition.x + mItemSize.X + mItemGap.X > availableSpace.x)
			{
				currentCursorPosition.x = startPosition.x;
				currentCursorPosition.y += mItemSize.Y + mItemGap.Y;
			}
			else
			{
				currentCursorPosition.x += mItemSize.X + mItemGap.X;
			}
		}

		/*
		* Draw files
		*/
		const Array<DomainFile*> files = mCurrentFolder->GetFiles();
		for (unsigned int i = 0; i < files.GetCursor(); i++)
		{
			DomainFile* pFile = files[i];

			TextureResource* pTexture = pFile->GetVisualizer()->OnPaint(pFile);
			if (pTexture == nullptr)
			{
				ImGui::Image(mInvalidIcon->GetTexture()->GetIsolatedResourceTable()->GetHandle(), {mItemSize.X,mItemSize.Y});
				continue;
			}

			ImGui::SetCursorPos(currentCursorPosition);
			ImGui::Image(pTexture->GetIsolatedResourceTable()->GetHandle(), { mItemSize.X,mItemSize.Y });

			if (currentCursorPosition.x + mItemSize.X + mItemGap.X > availableSpace.x)
			{
				currentCursorPosition.x = startPosition.x;
				currentCursorPosition.y += mItemSize.Y + mItemGap.Y;
			}
			else
			{
				currentCursorPosition.x += mItemSize.X + mItemGap.X;
			}
		}
	}
	void DomainObserverWindow::OnFileDrop(const String& path)
	{
		if (mCurrentFolder == nullptr)
			return;

		mCurrentFolder->CreateFileFromSource(path);
	}
	void DomainObserverWindow::OnFolderDrop(const String& path)
	{

	}

}