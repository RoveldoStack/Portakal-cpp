#include "SceneDescriptorYamlSerializer.h"

namespace Portakal
{
    void SceneDescriptorYamlSerializer::Serialize(YAML::Emitter& emitter, const Class* pObject)
    {
        const SceneDescriptor* pTarget = (const SceneDescriptor*)pObject;
    }
    void SceneDescriptorYamlSerializer::Deserialize(const YAML::Node& node, Class* pObject)
    {
        SceneDescriptor* pTarget = (SceneDescriptor*)pObject;
    }
}