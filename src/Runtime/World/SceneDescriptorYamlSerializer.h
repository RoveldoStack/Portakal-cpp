#pragma once
#include <Runtime/World/SceneDescriptor.h>
#include <Runtime/Yaml/YamlSerializer.h>
#include <Runtime/Yaml/YamlSerializerAttribute.h>

namespace Portakal
{
	class PORTAKAL_API SceneDescriptorYamlSerializer : public YamlSerializer
	{
		GENERATE_CLASS(SceneDescriptorYamlSerializer);
	public:
		SceneDescriptorYamlSerializer() = default;
		~SceneDescriptorYamlSerializer() = default;


		// Inherited via YamlSerializer
		virtual void Serialize(YAML::Emitter& emitter, const Class* pObject) override;
		virtual void Deserialize(const YAML::Node& node, Class* pObject) override;

	};

	START_GENERATE_TYPE(SceneDescriptorYamlSerializer);
	START_TYPE_PROPERTIES(SceneDescriptorYamlSerializer);
	REGISTER_BASE_TYPE(YamlSerializer);
	REGISTER_TYPE_ATTRIBUTE(YamlSerializerAttribute, typeof(SceneDescriptor));
	END_TYPE_PROPERTIES;
	HAS_DEFAULT_CONSTRUCTOR(SceneDescriptorYamlSerializer);
	END_GENERATE_TYPE(SceneDescriptorYamlSerializer);
}