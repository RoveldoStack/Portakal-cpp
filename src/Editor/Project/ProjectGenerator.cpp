#include "ProjectGenerator.h"
#include <Editor/Project/Project.h>
#include <Runtime/Yaml/Yaml.h>
#include <Runtime/Log/Log.h>


namespace Portakal
{
	void ProjectGenerator::GenerateSync(const String& name, const String& folderPath)
	{
		/*
		* Create project header
		*/
		Project project = { };
		project.Name = name;
		project.ID = Guid::Create();
		project.VersionMajor = 0;
		project.VersionMinor = 0;
		project.VersionPatch = 0;

		const String projectYaml = Yaml::ToYaml<Project>(&project);
		LOG("Yamlcontent", "->%s", *projectYaml);
		if (!PlatformDirectory::IsDirectoryExist(folderPath))
		{
			PlatformDirectory::Create(folderPath);
		}

		const String projectHeaderFilePath = folderPath + "/" + name + ".pproject";
		PlatformFile::Create(projectHeaderFilePath);
		PlatformFile::Write(projectHeaderFilePath, projectYaml);

		/*
		* Create sub folders
		*/
		PlatformDirectory::Create(folderPath + "/Settings");
		PlatformDirectory::Create(folderPath + "/Domain");
		PlatformDirectory::Create(folderPath + "/Codebase");
		PlatformDirectory::Create(folderPath + "/Cache");

		/*
		* Write default domain files
		*/

		/*
		* Create codebase solutions
		*/
	}
}