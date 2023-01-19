#pragma once
#include <Editor/Project/ProjectYaml.h>
#include <Runtime/Yaml/YamlSerializer.h>
#include <Runtime/Yaml/YamlSerializerAttribute.h>

namespace Portakal
{
	class PORTAKAL_API ProjectYamlSerializer : public YamlSerializer
	{
		GENERATE_CLASS(ProjectYamlSerializer);
	public:
		ProjectYamlSerializer() = default;
		~ProjectYamlSerializer() = default;

		virtual void Serialize(YAML::Emitter& emitter, const Class* pObject) override;
		virtual void Deserialize(const YAML::Node& node, Class* pObject) override;
	};

	START_GENERATE_TYPE(ProjectYamlSerializer);
	START_TYPE_PROPERTIES(ProjectYamlSerializer);
	REGISTER_TYPE_ATTRIBUTE(YamlSerializerAttribute, typeof(ProjectYaml));
	END_TYPE_PROPERTIES;
	CONCRETE_TYPE(ProjectYamlSerializer);
	END_GENERATE_TYPE(ProjectYamlSerializer);
}