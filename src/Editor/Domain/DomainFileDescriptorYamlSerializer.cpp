#include "DomainFileDescriptorYamlSerializer.h"

namespace Portakal
{
    void DomainFileDescriptorYamlSerializer::Serialize(YAML::Emitter& emitter, const Class* pObject)
    {
        const DomainFileDescriptor* pTarget = (const DomainFileDescriptor*)pObject;

        emitter << YAML::BeginDoc;

        emitter << YAML::BeginMap;

        emitter << YAML::Key << "Source File";
        emitter << YAML::Value << *pTarget->SourceFile;

        emitter << YAML::Key << "Resource Type";
        emitter << YAML::Value << *pTarget->ResourceType;

        emitter << YAML::Key << "ID";
        emitter << YAML::Value << *(Guid::ToString(pTarget->ID));

        emitter << YAML::EndMap;

        emitter << YAML::EndDoc;
    }
    void DomainFileDescriptorYamlSerializer::Deserialize(const YAML::Node& node, Class* pObject)
    {
        DomainFileDescriptor* pTarget = (DomainFileDescriptor*)pObject;

        pTarget->SourceFile = node["Source File"].as<std::string>().c_str();
        pTarget->ResourceType = node["Resource Type"].as<std::string>().c_str();
        pTarget->ID = Guid::FromString(node["ID"].as<std::string>().c_str());
    }
}