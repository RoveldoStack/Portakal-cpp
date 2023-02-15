#pragma once
#include <Editor/GUI/Window/EditorWindow.h>
#include <Runtime/Math/Vector2.h>

namespace Portakal
{
	class DomainFolder;
	class WindowEvent;
	class DragDropEvent;
	class EditorImageResource;
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
		void OnFolderDrop(const String& path);

		void ClearSelectedItems();
		void SelectFolder(DomainFolder* pFolder);
		void OpenFolder(DomainFolder* pFolder);
		void ReturnToParentFolder();
		void CreateFolder(const String& folderName);
	private:
		DomainFolder* mCurrentFolder;
		DomainFolder* mSelectedFolder;
		EditorImageResource* mInvalidIcon;
		EditorImageResource* mFolderIcon;
		Vector2F mItemSize;
		Vector2F mItemGap;

		char mFolderNameCache[PLATFORM_FOLDER_NAME_SIZE];
	};

	START_GENERATE_TYPE(DomainObserverWindow);
	START_TYPE_PROPERTIES(DomainObserverWindow);
	END_TYPE_PROPERTIES;
	CONCRETE_TYPE(DomainObserverWindow);
	END_GENERATE_TYPE(DomainObserverWindow);
}