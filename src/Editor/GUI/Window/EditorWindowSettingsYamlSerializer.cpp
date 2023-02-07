#include "EditorWindowSettingsYamlSerializer.h"

namespace Portakal
{
    void EditorWindowSettingsYamlSerializer::Serialize(YAML::Emitter& emitter, const Class* pObject)
    {
        const EditorWindowSettings* pTarget = (const EditorWindowSettings*)pObject;

        emitter << YAML::BeginDoc;

        emitter << YAML::BeginMap;

        emitter << YAML::Key << "Windows";

        emitter << YAML::BeginSeq;

        emitter << YAML::Value;

        for (unsigned int i = 0; i < pTarget->Windows.GetCursor(); i++)
        {
            const EditorWindowSetting setting = pTarget->Windows[i];

            emitter << YAML::BeginMap;

            emitter << YAML::Key << "Name";
            emitter << YAML::Value << *setting.Name;

            emitter << YAML::Key << "ID";
            emitter << YAML::Value << *Guid::ToString(setting.ID);

            emitter << YAML::Key << "DockState";
            emitter << YAML::Value << *String::GetFromInteger((unsigned int)setting.DockState);

            emitter << YAML::Key << "OwnerID";
            emitter << YAML::Value << *Guid::ToString(setting.OwnerID);

            emitter << YAML::EndMap;
        }

        emitter << YAML::EndSeq;

        emitter << YAML::EndMap;

        emitter << YAML::EndDoc;
    }
    void EditorWindowSettingsYamlSerializer::Deserialize(const YAML::Node& node, Class* pObject)
    {
        EditorWindowSettings* pTarget = (EditorWindowSettings*)pObject;

        const YAML::Node& windows = node["Windows"];
        for (YAML::const_iterator it = windows.begin(); it != windows.end(); ++it)
        {
            const YAML::Node& windowNode = *it;

            EditorWindowSetting setting = {};
            setting.Name = windowNode["Name"].as<std::string>().c_str();
            setting.ID = Guid::FromString(windowNode["ID"].as<std::string>().c_str());
            setting.DockState = (EditorWindowDockState)windowNode["DockState"].as<unsigned int>();
            setting.OwnerID = Guid::FromString(windowNode["OwnerID"].as<std::string>().c_str());

            pTarget->Windows.Add(setting);
        }
    }
}