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
#include <Editor/Asset/Serializers/TextAssetSerializer.h>
#include <Editor/Asset/Importers/TextureAssetImporter.h>
#include <Editor/Domain/DomainFile.h>
#include <Editor/Asset/IAssetVisualizer.h>
#include <Runtime/Assert/Assert.h>
#include <Runtime/Platform/PlatformExplorer.h>
#include <Runtime/Memory/Memory.h>
#include <Editor/Asset/IAssetSerializer.h>
#include <Editor/Asset/Visualizers/TextureAssetVisualizer.h>
#include <Editor/Asset/Serializers/TextureAssetSerializer.h>
#include <Editor/GUI/Window/Templates/AuthorizationToolWindow.h>
#include <Editor/GUI/Window/EditorWindowAPI.h>
#include <Editor/Asset/AuthorizationTools/TextureAuthorizationTool.h>
#include <Editor/Renderer/ImGuiAPI.h>
#include <Editor/Renderer/ImGuiRenderer.h>
#include <Editor/Renderer/ImGuiTextureBinding.h>
#include <Editor/Asset/Visualizers/SceneAssetVisualizer.h>
#include <Runtime/World/Scene.h>
#include <Runtime/World/SceneAPI.h>
#include <Runtime/Resource/Resource.h>
#include <Runtime/World/Scene.h>
#include <Editor/Asset/IAssetOpenOperation.h>


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
				OnFolderDrop(mCurrentFolder,path);
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

		pTargetWindow->RegisterEventListener(GENERATE_MEMBER_DELEGATE1(this, DomainObserverWindow::OnEvent, void, const WindowEvent*));

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
		mItemSize = { 96,96 };
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
		pTargetWindow->RemoveEventListener(GENERATE_MEMBER_DELEGATE1(this, DomainObserverWindow::OnEvent, void, const WindowEvent*));
	}

	void DomainObserverWindow::OnPaint()
	{
		/*
		* Validate current folder
		*/
		if (mCurrentFolder == nullptr)
			return;

		/*
		* Handle pre events
		*/
		if (ImGui::IsKeyPressed(ImGuiKey_Delete))
		{
			DeleteSelectedItems();
		}

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

			/*
			* Draw selectable
			*/
			ImGui::SetCursorPos(currentCursorPosition);
			const String tag = "##" + pFolder->GetFolderName();
			if (ImGui::Selectable(*tag, mSelectedFolders.Has(pFolder), ImGuiSelectableFlags_AllowDoubleClick, {mItemSize.X,mItemSize.Y}))
			{
				if (ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
				{
					OpenFolder(pFolder);
				}
				else
				{
					SelectFolder(pFolder);
				}
			}
			ImGui::SetCursorPos(currentCursorPosition);

			/*
			* Draw image
			*/
			ImGui::Image(mFolderIcon->GetImGuiTexture()->GetBinding(), {mItemSize.X,mItemSize.Y});

			/*
			* Draw text
			*/
			const ImVec2 textSize = ImGui::CalcTextSize(*pFolder->GetFolderName());
			const float widthCoef = (mItemSize.X / 2)-(textSize.x / 2);
			const ImVec2 textPosition = { currentCursorPosition.x + widthCoef,currentCursorPosition.y + mItemSize.Y + 10 };

			ImGui::SetCursorPos(textPosition);
			ImGui::Text(*pFolder->GetFolderName());

			if (currentCursorPosition.x + mItemSize.X + mItemGap.X > availableSpace.x)
			{
				currentCursorPosition.x = startPosition.x;
				currentCursorPosition.y += mItemSize.Y + mItemGap.Y + 24;
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

			/*
			* Draw selectable
			*/
			ImGui::SetCursorPos(currentCursorPosition);
			const String tag = "##" + pFile->GetName();
			if (ImGui::Selectable(*tag, mSelectedFiles.Has(pFile), ImGuiSelectableFlags_AllowDoubleClick, { mItemSize.X,mItemSize.Y }))
			{
				if (ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
				{
					OpenFile(pFile);
				}
				else
				{
					SelectFile(pFile);
				}
			}
			ImGui::SetCursorPos(currentCursorPosition);


			/*
			* Draw image
			*/
			IAssetVisualizer* pVisualizer = pFile->GetVisualizer();
			TextureResource* pTexture = pVisualizer != nullptr ? pVisualizer->OnPaint(pFile) : nullptr;

			const unsigned int textureWidth = pTexture->GetWidth();
			const unsigned int textureHeight = pTexture->GetHeight();

			ImGui::SetCursorPos(currentCursorPosition);
			if (pVisualizer == nullptr || pTexture == nullptr)
			{
				ImGui::Image(mInvalidIcon->GetImGuiTexture()->GetBinding(), {mItemSize.X,mItemSize.Y});

			}
			else
			{
				ImGuiTextureBinding* pImGuiTexture = ImGuiAPI::GetDefaultRenderer()->GetOrCreateTextureBinding(pTexture);

				if(pImGuiTexture == nullptr)
					ImGui::Image(mInvalidIcon->GetImGuiTexture()->GetBinding(), { mItemSize.X,mItemSize.Y });
				else
					ImGui::Image(pImGuiTexture->GetBinding(), {mItemSize.X,mItemSize.Y});
			}
			
			/*
			* Draw text
			*/
			const ImVec2 textSize = ImGui::CalcTextSize(*pFile->GetName());
			const float widthCoef = (mItemSize.X / 2) - (textSize.x / 2);
			const ImVec2 textPosition = { currentCursorPosition.x + widthCoef,currentCursorPosition.y + mItemSize.Y + 10 };

			ImGui::SetCursorPos(textPosition);
			ImGui::Text(*pFile->GetName());

			if (currentCursorPosition.x + mItemSize.X + mItemGap.X > availableSpace.x)
			{
				currentCursorPosition.x = startPosition.x;
				currentCursorPosition.y += mItemSize.Y + mItemGap.Y + 24;
			}
			else
			{
				currentCursorPosition.x += mItemSize.X + mItemGap.X;
			}
		}

		/*
		* Handle post events
		*/ 
		if (ImGui::IsWindowFocused() && !ImGui::IsAnyItemHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Right))// right click to empty space
		{
			ImGui::OpenPopup("ContextPopup");
		}
		if (ImGui::IsKeyPressed(ImGuiKey_Backspace)) // moving backwards in the folder hierarchy
		{
			ReturnToParentFolder();
		}
		if (!ImGui::IsAnyItemHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Left)) // clearing selected items
		{
			ClearSelectedItems();
		}
		
		/*
		* Handle popups
		*/
		if (ImGui::BeginPopup("ContextPopup")) // context menu popup
		{
			ImGui::Text("Create");
			ImGui::Separator();
			ImGui::Spacing();

			if (ImGui::Selectable("Open in explorer"))
			{
				PlatformExplorer::OpenExplorer(mCurrentFolder->GetFolderPath());
				ImGui::EndPopup();
			}
			else if (ImGui::Selectable("Folder"))
			{
				ImGui::CloseCurrentPopup();
				ImGui::EndPopup();
				ImGui::OpenPopup("FolderCreatePopup");
			}
			else if (ImGui::Selectable("Scene"))
			{
				ImGui::CloseCurrentPopup();
				ImGui::EndPopup();
				ImGui::OpenPopup("SceneCreatePopup");
			}
			else if (ImGui::Selectable("Material"))
			{

			}
			else if (ImGui::Selectable("Shader"))
			{

			}
			else if (ImGui::Selectable("Sampler"))
			{

			}
			else
			{
				ImGui::EndPopup();
			}
		}

		if (ImGui::BeginPopup("FolderCreatePopup")) // folder create popup
		{
			ImGui::Text("Create Folder");
			ImGui::Separator();
			ImGui::Spacing();

			ImGui::Text("Name: ");
			ImGui::SameLine();
			ImGui::InputText("##folderNameInput",mFolderNameCache, PLATFORM_FOLDER_NAME_SIZE);

			if (ImGui::Button("Create"))
			{
				CreateFolder(mFolderNameCache);
				ImGui::CloseCurrentPopup();
			}

			ImGui::EndPopup();
		}
		if (ImGui::BeginPopup("SceneCreatePopup")) // scene create popup
		{
			ImGui::Text("Create Scene");
			ImGui::Separator();
			ImGui::Spacing();

			ImGui::Text("Name: ");
			ImGui::SameLine();
			ImGui::InputText("##sceneNameInput", mSceneNameCache, PLATFORM_FOLDER_NAME_SIZE);

			if (ImGui::Button("Create"))
			{
				String name = mSceneNameCache;
				name += ".pscene";

				CreateResourceFile(name, "scene");
				ImGui::CloseCurrentPopup();

				Memory::Set(mSceneNameCache, 0, PLATFORM_FILE_NAME_SIZE);
			}
			ImGui::EndPopup();
		}

	}
	void DomainObserverWindow::OnFileDrop(const String& path)
	{
		if (mCurrentFolder == nullptr)
			return;

		mCurrentFolder->CreateFileFromSource(path);
	}
	void DomainObserverWindow::OnFolderDrop(DomainFolder* pTargetFolder,const String& path)
	{
		/*
		* Create folder
		*/
		DomainFolder* pRootFolder = pTargetFolder->CreateFolder(PlatformDirectory::GetName(path));
		if (pRootFolder == nullptr)
		{
			LOG("DomainObserverWindow", "Failed to drop the folder");
			return;
		}

		/*
		* Iterate and create folders
		*/
		Array<String> subFolderPaths;
		PlatformDirectory::GetFolderNames(path + "\\", subFolderPaths);

		for (unsigned int i = 0; i < subFolderPaths.GetCursor(); i++)
		{
			OnFolderDrop(pRootFolder,subFolderPaths[i]);
		}

		/*
		* Iterate and create files
		*/
		Array<String> files;
		PlatformDirectory::GetFileNames(path+"\\", files);
		for (unsigned int i = 0; i < files.GetCursor(); i++)
		{
			pRootFolder->CreateFileFromSource(files[i]);
		}
	}

	void DomainObserverWindow::ClearSelectedItems()
	{
		mSelectedFolders.Clear();
		mSelectedFiles.Clear();
	}

	void DomainObserverWindow::DeleteSelectedItems()
	{
		/*
		* Delete files
		*/
		for (unsigned int i = 0; i < mSelectedFiles.GetCursor(); i++)
			mSelectedFiles[i]->Delete();
		mSelectedFiles.Clear();

		/*
		* Delete folders
		*/
		for (unsigned int i = 0; i < mSelectedFolders.GetCursor(); i++)
			mSelectedFolders[i]->Delete();
		mSelectedFolders.Clear();
	}

	void DomainObserverWindow::SelectFolder(DomainFolder* pFolder)
	{
		if (!ImGui::IsKeyDown(ImGuiKey_LeftCtrl))
			ClearSelectedItems();
		
		mSelectedFolders.Add(pFolder);
	}

	void DomainObserverWindow::OpenFolder(DomainFolder* pFolder)
	{
		if (pFolder == nullptr)
			return;

		mCurrentFolder = pFolder;

		ClearSelectedItems();
	}

	void DomainObserverWindow::ReturnToParentFolder()
	{
		if (mCurrentFolder == nullptr || mCurrentFolder->GetParentFolder() == nullptr)
			return;

		mCurrentFolder = mCurrentFolder->GetParentFolder();
	}

	void DomainObserverWindow::CreateFolder(const String& folderName)
	{
		mCurrentFolder->CreateFolder(folderName);

		Memory::Set(mFolderNameCache, 0, PLATFORM_FOLDER_NAME_SIZE);
	}

	void DomainObserverWindow::CreateResourceFile(const String& name, const String& type)
	{
		mCurrentFolder->CreateResourceFile(name,type);
	}

	void DomainObserverWindow::SelectFile(DomainFile* pFile)
	{
		if (!ImGui::IsKeyDown(ImGuiKey_LeftCtrl))
			ClearSelectedItems();

		mSelectedFiles.Add(pFile);
	}

	void DomainObserverWindow::OpenFile(DomainFile* pFile)
	{
		/*
		* Run open operation interfaces
		*/
		pFile->OpenSync();

		/*
		* Validate if given domain file has a target authorization tool
		*/
		if (pFile->GetAuthorizationTool() == nullptr)
			return;

		
		AuthorizationToolWindow* pWindow = EditorWindowAPI::Create<AuthorizationToolWindow>();
		pWindow->SetToolData(pFile);
	}

}