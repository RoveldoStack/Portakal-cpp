#pragma once
#include <Editor/GUI/Window/EditorWindow.h>
#include <Runtime/Math/Vector2F.h>

namespace Portakal
{
	class DomainFolder;
	class WindowEvent;
	class DragDropEvent;
	class EditorImageResource;
	class DomainFile;

	PCLASS();
	class PORTAKAL_API DomainObserverWindow : public EditorWindow
	{
		GENERATE_CLASS(DomainObserverWindow);
	public:
		DomainObserverWindow() = default;
		~DomainObserverWindow() = default;
	private:
		void OnEvent(const WindowEvent* pEvent);
		// Inherited via EditorWindow
		virtual void OnShow() override;
		virtual void OnHide() override;
		virtual void OnInitialize() override;
		virtual void OnFinalize() override;
		virtual void OnPaint() override;

	private:
		void OnFileDrop(const String& path);
		void OnFolderDrop(DomainFolder* pTargetFolder,const String& path);

		void ClearSelectedItems();
		void DeleteSelectedItems();

		void SelectFolder(DomainFolder* pFolder);
		void OpenFolder(DomainFolder* pFolder);
		void ReturnToParentFolder();
		void CreateFolder(const String& folderName);

		void CreateResourceFile(const String& name, const String& type);
		void SelectFile(DomainFile* pFile);
		void OpenFile(DomainFile* pFile);
	private:
		DomainFolder* mCurrentFolder;
		Array<DomainFolder*> mSelectedFolders;
		Array<DomainFile*> mSelectedFiles;
		EditorImageResource* mInvalidIcon;
		EditorImageResource* mFolderIcon;
		Vector2F mItemSize;
		Vector2F mItemGap;


		char mNameCache[PLATFORM_FILE_NAME_SIZE];
	};

#include "DomainObserverWindow.reflect.h"
}