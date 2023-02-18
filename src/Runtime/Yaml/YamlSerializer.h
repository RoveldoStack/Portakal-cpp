#pragma once
#include <Runtime/Reflection/Reflection.h>
#include <Libs/Yaml/include/yaml-cpp/yaml.h>

namespace Portakal
{
	class PORTAKAL_API YamlSerializer : public Class
	{
		GENERATE_CLASS(YamlSerializer);
	public:
		YamlSerializer() = default;
		~YamlSerializer() = default;

		virtual void Serialize(YAML::Emitter& emitter, const Class* pObject) = 0;
		virtual void Deserialize(const YAML::Node& node, Class* pObject) = 0;
	};

	START_GENERATE_TYPE(YamlSerializer);
		START_TYPE_PROPERTIES(YamlSerializer);
		END_TYPE_PROPERTIES;
	NO_DEFAULT_CONSTRUCTOR;
	END_GENERATE_TYPE(YamlSerializer);
}