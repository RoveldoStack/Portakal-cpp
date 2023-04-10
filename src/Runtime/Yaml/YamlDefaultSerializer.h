#pragma once
#include <Runtime/Yaml/IYamlSerializer.h>

namespace Portakal
{
	class PORTAKAL_API YamlDefaultSerializer : public IYamlSerializer
	{
		GENERATE_CLASS(YamlDefaultSerializer);
	public:
		// Inherited via IYamlSerializer
		virtual void Serialize(YAML::Emitter& emitter, const Class* pObject) override;
		virtual void Deserialize(const YAML::Node& node, Class* pObject) override;
	private:

	};
}