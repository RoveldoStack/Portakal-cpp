#include "ProjectModule.h"
#include <Runtime/Platform/PlatformFile.h>
#include <Runtime/Platform/PlatformDirectory.h>
#include <Runtime/Platform/PlatformDialog.h>
#include <Runtime/Platform/PlatformMessage.h>
#include <Runtime/Yaml/Yaml.h>
#include <Editor/Project/ProjectYamlSerializer.h>
#include <Runtime/Message/MessageAPI.h>
#include <Editor/Project/ProjectAPI.h>
#include <Editor/Project/ProjectPaths.h>
namespace Portakal
{
    void ProjectModule::OnInitialize()
    {
        /*
        * Test folder
        */
        if (!PlatformDirectory::IsDirectoryExist(mCreateParams.FolderPath))
        {
            PlatformMessage::ShowMessageBox("ProjectModule", "Unable to locate project folder");
            PostQuitMessage("Target project folder is missing!");
            return;
        }

        /*
        * Test file
        */
        const String projectFilePath = mCreateParams.FolderPath + "\\" + mCreateParams.Name + ".pproject";
        if (!PlatformFile::IsExist(projectFilePath))
        {
            PlatformMessage::ShowMessageBox("ProjectModule", "Unable to locate project file");
            PostQuitMessage("Target project file is missing");
            return;
        }

        /*
        * Load project
        */
        String projectYamlContent;
        if (!PlatformFile::Read(projectFilePath, projectYamlContent))
        {
            PlatformMessage::ShowMessageBox("Project Module", "Unable to read from project file!");
            PostQuitMessage("Couldnt read from the project file");
            return;
        }

        MessageAPI::BroadcastMessage(projectYamlContent);
        ProjectYaml projectYAML = {};
        Yaml::ToObject(projectYamlContent,&projectYAML);

        Project project = {};
        project.ProjectFolderAbsolutePath = mCreateParams.FolderPath;
        project.Name = projectYAML.Name;
        project.ID = projectYAML.ID;
        project.VersionMinor = projectYAML.VersionMinor;
        project.VersionMajor = projectYAML.VersionMajor;
        project.VersionPatch = projectYAML.VersionPatch;

        /*
        * Set project
        */
        mAPI = new ProjectAPI(project);

        /*
        * Setup project paths
        */
        ProjectPaths::sProjectFolder = mCreateParams.FolderPath;
        ProjectPaths::sDomainFolder = mCreateParams.FolderPath + "\\Domain";
        ProjectPaths::sSettingsFolder = mCreateParams.FolderPath + "\\Settings";
    }
    void ProjectModule::OnFinalize()
    {
        delete mAPI;
    }
    void ProjectModule::OnPreTick()
    {

    }
    void ProjectModule::OnTick()
    {

    }
    void ProjectModule::OnPostTick()
    {

    }
    void ProjectModule::PreValidate()
    {

    }
    void ProjectModule::PostValidate()
    {

    }
    void ProjectModule::OnEvent(WindowEvent* pEvent)
    {

    }
}