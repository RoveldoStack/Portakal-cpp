#include "ShaderObjectDescriptorYamlSerializer.h"
#include <Runtime/Resource/Shader/ShaderObject.h>

namespace Portakal
{
    void ShaderObjectDescriptorYamlSerializer::Serialize(YAML::Emitter& emitter, const Class* pObject)
    {
        const ShaderObjectDescriptor* pDescriptor = (const ShaderObjectDescriptor*)pObject;

        emitter << YAML::BeginDoc;

        emitter << YAML::BeginMap;

        emitter << YAML::Key << "Stage";
        emitter << YAML::Value << (long long)pDescriptor->Stage;

        emitter << YAML::Key << "Source";
        if(pDescriptor->Source.GetSource() == nullptr)
            emitter << YAML::Value << "";
        else
            emitter << YAML::Value << *pDescriptor->Source;

        emitter << YAML::Key << "EntryPoint";
        if (pDescriptor->EntryPoint.GetSource() == nullptr)
            emitter << YAML::Value << "";
        else
            emitter << YAML::Value << *pDescriptor->EntryPoint;

        emitter << YAML::EndMap;

        emitter << YAML::EndDoc;
    }
    void ShaderObjectDescriptorYamlSerializer::Deserialize(const YAML::Node& node, Class* pObject)
    {
        ShaderObjectDescriptor* pDescriptor = (ShaderObjectDescriptor*)pObject;

        const ShaderStage stage = (ShaderStage)node["Stage"].as<long long>();
        const String source = node["Source"].as<std::string>().c_str();
        const String entryPoint = node["EntryPoint"].as<std::string>().c_str();

        pDescriptor->Stage = stage;
        pDescriptor->Source = source;
        pDescriptor->EntryPoint = entryPoint;
    }
}