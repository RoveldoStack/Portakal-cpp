#include "GUIWindowModule.h"
#include <Libs/ImGui/imgui.h>
#include <Libs/ImGui/imgui_internal.h>
#include <Runtime/Log/Log.h>
#include <Editor/GUI/Window/EditorWindow.h>
#include <Editor/GUI/Window/EditorWindowDockState.h>
#include <Editor/GUI/Window/EditorWindowAPI.h>

namespace Portakal
{
	void GUIWindowModule::OnInitialize()
	{
		/*
		* Initialize api
		*/
		mAPI = new EditorWindowAPI();
	}
	void GUIWindowModule::OnFinalize()
	{
		delete mAPI;
		mAPI = nullptr;
	}
	void GUIWindowModule::OnPreTick()
	{

	}
	void GUIWindowModule::OnTick()
	{
		/*
		* Start docking window
		*/
		const ImVec2 screenSize = ImGui::GetMainViewport()->Size;
		const ImVec2 position = ImGui::GetMainViewport()->Pos;

		ImGui::SetNextWindowSize(screenSize);
		ImGui::SetNextWindowPos(position);
		ImGui::SetNextWindowViewport(ImGui::GetMainViewport()->ID);

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 0,0 });
		ImGui::PushStyleColor(ImGuiCol_WindowBg, { 0,0,0,1.0f });
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0);

		ImGui::Begin("Dockspace", &mDockState,
			ImGuiWindowFlags_NoCollapse |
			ImGuiWindowFlags_NoMove |
			ImGuiWindowFlags_NoScrollbar |
			ImGuiWindowFlags_NoResize |
			ImGuiWindowFlags_NoTitleBar |
			ImGuiWindowFlags_NoBringToFrontOnFocus |
			ImGuiWindowFlags_MenuBar
		);

		ImGui::PopStyleVar();
		ImGui::PopStyleVar();
		ImGui::PopStyleColor();

		ImGuiID dockspaceID = ImGui::GetID("EditorDockspace");

		ImGui::DockSpace(dockspaceID, { 0,0 });

		if (!mLayoutInitialized)
		{
			/*
			* Clear nodes
			*/
			ImGui::DockBuilderRemoveNode(dockspaceID);

			/*
			* Add the dockspace node and properties
			*/
			ImGui::DockBuilderAddNode(dockspaceID, ImGuiDockNodeFlags_DockSpace);
			ImGui::DockBuilderSetNodeSize(dockspaceID, screenSize);

			/*
			* Split the view
			*/
			unsigned int dockIDLeft = ImGui::DockBuilderSplitNode(dockspaceID, ImGuiDir_Left,0.35f,nullptr,&dockspaceID);
			unsigned int dockIDRight = ImGui::DockBuilderSplitNode(dockspaceID, ImGuiDir_Right, 0.35f, nullptr, &dockspaceID);
			unsigned int dockIDUp = ImGui::DockBuilderSplitNode(dockspaceID, ImGuiDir_Up, 0.25f, nullptr, &dockspaceID);
			unsigned int dockIDDown = ImGui::DockBuilderSplitNode(dockspaceID, ImGuiDir_Down, 0.4f, nullptr, &dockspaceID);

			Array<unsigned int> nodes = { 0,dockspaceID,dockIDLeft ,dockIDRight ,dockIDUp ,dockIDDown };

			/*
			* Dock the windows
			*/
			Array<EditorWindow*> windows;
			for (unsigned int i = 0; i < windows.GetCursor(); i++)
			{
				EditorWindow* pWindow = windows[i];
				const String name = pWindow->GetType()->GetTypeName();

				if (pWindow->GetDockState() == EditorWindowDockState::None)
					continue;

				const unsigned int dockID = nodes[(int)pWindow->GetDockState()];

				ImGui::DockBuilderDockWindow(*name, dockID);
			}
			ImGui::DockBuilderFinish(dockspaceID);
			mLayoutInitialized = true;
		}

		/*
		* Update api
		*/
		mAPI->Paint();

		/*
		* Update windows
		*/
		ImGui::End();
	}
	void GUIWindowModule::OnPostTick()
	{

	}
	void GUIWindowModule::PreValidate()
	{

	}
	void GUIWindowModule::PostValidate()
	{

	}
	void GUIWindowModule::OnEvent(WindowEvent* pEvent)
	{

	}
}