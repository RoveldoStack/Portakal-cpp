#include "ProjectYamlSerializer.h"

namespace Portakal
{
	void ProjectYamlSerializer::Serialize(YAML::Emitter& emitter, const Class* pObject)
	{
		const ProjectYaml* pTarget = (const ProjectYaml*)pObject;

		emitter << YAML::BeginDoc;

		emitter << YAML::BeginMap;

		emitter << YAML::Key << "Name";
		emitter << YAML::Value << *pTarget->Name;

		emitter << YAML::Key << "Major Version";
		emitter << YAML::Value << *String::GetFromInteger(pTarget->VersionMajor);

		emitter << YAML::Key << "Minor Version";
		emitter << YAML::Value << *String::GetFromInteger(pTarget->VersionMinor);

		emitter << YAML::Key << "Patch Version";
		emitter << YAML::Value << *String::GetFromInteger(pTarget->VersionPatch);

		const String guidString = Guid::ToString(pTarget->ID);

		emitter << YAML::Key << "ID";
		emitter << YAML::Value << *guidString;

		emitter << YAML::EndMap;

		emitter << YAML::EndDoc;
	}
	void ProjectYamlSerializer::Deserialize(const YAML::Node& node, Class* pObject)
	{
		ProjectYaml* pTarget = (ProjectYaml*)pObject;

		pTarget->Name = node["Name"].as<std::string>().c_str();

		pTarget->VersionMajor = node["Major version"].as<unsigned int>();
		pTarget->VersionMinor = node["Minor version"].as<unsigned int>();
		pTarget->VersionPatch = node["Patch version"].as<unsigned int>();

		pTarget->ID = Guid::FromString(node["ID"].as<std::string>().c_str());
	}
}