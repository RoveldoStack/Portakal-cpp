#include "GUIWindowModule.h"
#include <Libs/ImGui/imgui.h>
#include <Libs/ImGui/imgui_internal.h>
#include <Runtime/Log/Log.h>
#include <Editor/GUI/Window/EditorWindow.h>
#include <Editor/GUI/Window/EditorWindowDockState.h>
#include <Editor/GUI/Window/EditorWindowAPI.h>
#include <Editor/GUI/Window/EditorWindowSettingsYamlSerializer.h>
#include <Editor/Project/ProjectPaths.h>
#include <Runtime/Platform/PlatformFile.h>
#include <Runtime/Platform/PlatformDirectory.h>
#include <Runtime/Yaml/Yaml.h>
#include <Runtime/Message/MessageAPI.h>
#include <Runtime/Platform/PlatformMessage.h>

namespace Portakal
{
	void GUIWindowModule::OnInitialize()
	{
		/*
		* Check if settings exists
		*/
		const String settingsPath = ProjectPaths::GetSettingsFolder() + "\\WindowSettings.psettings";
		if (!PlatformFile::IsExist(settingsPath))
		{
			CreateDefaultSettings();
		}

		LoadWindowsFromFile();
	}
	void GUIWindowModule::OnFinalize()
	{
		SaveSettingsToFile();
		EditorWindowAPI::ClearAllWindows();
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
			unsigned int dockIDLeft = ImGui::DockBuilderSplitNode(dockspaceID, ImGuiDir_Left,0.15f,nullptr,&dockspaceID);
			unsigned int dockIDRight = ImGui::DockBuilderSplitNode(dockspaceID, ImGuiDir_Right, 0.25f, nullptr, &dockspaceID);
			unsigned int dockIDUp = ImGui::DockBuilderSplitNode(dockspaceID, ImGuiDir_Up, 0.25f, nullptr, &dockspaceID);
			unsigned int dockIDDown = ImGui::DockBuilderSplitNode(dockspaceID, ImGuiDir_Down, 0.4f, nullptr, &dockspaceID);

			Array<unsigned int> nodes = { 0,dockspaceID,dockIDLeft ,dockIDRight ,dockIDUp ,dockIDDown };

			/*
			* Dock the windows
			*/
			Array<EditorWindow*> windows = mAPI->GetWindows();
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
		EditorWindowAPI::Paint();

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
		/*
		* Validate if settings exists
		*/
		const String path = ProjectPaths::GetSettingsFolder() + "\\WindowSettings.psettings";
		if (!PlatformFile::IsExist(path))
		{
			if (!PlatformFile::Create(path))
			{
				PlatformMessage::ShowMessageBox("Window Module", "Couldnt create WindowSettings during Pre-validation");
				return;
			}
		}

		/*
		* Write current settings
		*/
		SaveSettingsToFile();

		/*
		* Clears all the windows
		*/
		EditorWindowAPI::ClearAllWindows();
	}
	void GUIWindowModule::PostValidate()
	{
		LoadWindowsFromFile();
	}
	void GUIWindowModule::OnEvent(WindowEvent* pEvent)
	{

	}
	void GUIWindowModule::CreateDefaultSettings()
	{
		/*
		* Get default
		*/
		EditorWindowSettings defaultSettings = EditorWindowSettings::Default();

		/*
		* Write default
		*/
		String yamlContent = Yaml::ToYaml(&defaultSettings);

		if (!PlatformFile::Write(ProjectPaths::GetSettingsFolder() + "\\WindowSettings.psettings", yamlContent))
		{
			MessageAPI::BroadcastMessage("Unable to write default WindowSettings");
			return;
		}
	}
	void GUIWindowModule::SaveSettingsToFile()
	{
		/*
		* Check file
		*/
		const String path = ProjectPaths::GetSettingsFolder() + "\\WindowSettings.psettings";
		if (!PlatformFile::IsExist(path))
		{
			if (!PlatformFile::Create(path))
			{
				PlatformMessage::ShowMessageBox("Window Module", "Unable to create WindowSettings file");
				return;
			}
		}

		/*
		* Get current state as settings
		*/
		EditorWindowSettings settings = {};
		const Array<EditorWindow*> windows = mAPI->GetWindows();
		for (unsigned int i = 0; i < windows.GetCursor(); i++)
		{
			EditorWindow* pWindow = windows[i];

			EditorWindowSetting setting = {};
			setting.Name = pWindow->GetType()->GetTypeName();
			setting.ID = pWindow->GetID();
			setting.DockState = pWindow->GetDockState();

			settings.Windows.Add(setting);
		}

		/*
		* Write to file
		*/
		String yamlContent = Yaml::ToYaml(&settings);
		if (!PlatformFile::Write(path, yamlContent))
		{
			PlatformMessage::ShowMessageBox("Window Module", "Failed to write the current windows into settings file");
		}

	}
	void GUIWindowModule::LoadWindowsFromFile()
	{
		const String settingsPath = ProjectPaths::GetSettingsFolder() + "\\WindowSettings.psettings";

		/*
		* Load the settings file
		*/
		String yamlContent;
		if (!PlatformFile::Read(settingsPath, yamlContent))
		{
			PlatformMessage::ShowMessageBox("Window Module", "Failed to read from WindowSettings");
			PostQuitMessage("Failed to read from WindowSettings file");
			return;
		}

		EditorWindowSettings settings = {};
		Yaml::ToObject(yamlContent, &settings);

		/*
		* Create window
		*/
		for (unsigned int i = 0; i < settings.Windows.GetCursor(); i++)
		{
			const EditorWindowSetting setting = settings.Windows[i];

			EditorWindowAPI::CreateFromSetting(setting);
		}
	}
}