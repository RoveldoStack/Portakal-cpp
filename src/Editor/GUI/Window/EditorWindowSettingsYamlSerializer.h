#pragma once
#include <Runtime/Yaml/YamlSerializer.h>
#include <Runtime/Yaml/YamlSerializerAttribute.h>
#include <Editor/GUI/Window/EditorWindowSettings.h>

namespace Portakal
{
	class PORTAKAL_API EditorWindowSettingsYamlSerializer : public YamlSerializer
	{
		GENERATE_CLASS(EditorWindowSettingsYamlSerializer);
	public:
		EditorWindowSettingsYamlSerializer() = default;
		~EditorWindowSettingsYamlSerializer() = default;

		virtual void Serialize(YAML::Emitter& emitter, const Class* pObject) override;
		virtual void Deserialize(const YAML::Node& node, Class* pObject) override;
	};

	START_GENERATE_TYPE(EditorWindowSettingsYamlSerializer);
	START_TYPE_PROPERTIES(EditorWindowSettingsYamlSerializer);
	REGISTER_TYPE_ATTRIBUTE(YamlSerializerAttribute, typeof(EditorWindowSettings));
	END_TYPE_PROPERTIES;
	HAS_DEFAULT_CONSTRUCTOR(EditorWindowSettingsYamlSerializer);
	END_GENERATE_TYPE(EditorWindowSettingsYamlSerializer);
}