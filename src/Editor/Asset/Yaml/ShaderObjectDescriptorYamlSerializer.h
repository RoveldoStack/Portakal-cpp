#pragma
#include <Runtime/Resource/Shader/ShaderObjectDescriptor.h>
#include <Runtime/Yaml/IYamlSerializer.h>
#include <Runtime/Yaml/YamlSerializerAttribute.h>

namespace Portakal
{
	class PORTAKAL_API ShaderObjectDescriptorYamlSerializer : public IYamlSerializer
	{
		GENERATE_CLASS(ShaderObjectDescriptorYamlSerializer);
	public:
		ShaderObjectDescriptorYamlSerializer() = default;
		~ShaderObjectDescriptorYamlSerializer() = default;


		virtual void Serialize(YAML::Emitter& emitter, const Class* pObject) override;
		virtual void Deserialize(const YAML::Node& node, Class* pObject) override;

	};

	START_GENERATE_TYPE(ShaderObjectDescriptorYamlSerializer);
	START_TYPE_PROPERTIES(ShaderObjectDescriptorYamlSerializer);
	REGISTER_BASE_TYPE(IYamlSerializer);
	END_TYPE_PROPERTIES;
	HAS_DEFAULT_CONSTRUCTOR(ShaderObjectDescriptorYamlSerializer);
	END_GENERATE_TYPE(ShaderObjectDescriptorYamlSerializer);
}