#pragma once
#include <Runtime/Reflection/Reflection.h>
#include <Libs/Yaml/include/yaml-cpp/yaml.h>

namespace Portakal
{
	/// <summary>
	/// Serialization interface for the yaml, which authors both serialization and deserialization implementation
	/// </summary>
	class PORTAKAL_API IYamlSerializer : public Class
	{
		GENERATE_CLASS(IYamlSerializer);
	public:
		IYamlSerializer() = default;
		~IYamlSerializer() = default;

		/// <summary>
		/// The serialization implementation
		/// </summary>
		/// <param name="emitter"></param>
		/// <param name="pObject"></param>
		virtual void Serialize(YAML::Emitter& emitter, const Class* pObject) = 0;

		/// <summary>
		/// The deserialization implementation
		/// </summary>
		/// <param name="node"></param>
		/// <param name="pObject"></param>
		virtual void Deserialize(const YAML::Node& node, Class* pObject) = 0;
	};

	START_GENERATE_TYPE(IYamlSerializer);
		START_TYPE_PROPERTIES(IYamlSerializer);
		END_TYPE_PROPERTIES;
	NO_DEFAULT_CONSTRUCTOR;
	END_GENERATE_TYPE(IYamlSerializer);
}