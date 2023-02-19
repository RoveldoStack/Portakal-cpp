#pragma once
#include <Editor/Domain/DomainFileDescriptor.h>
#include <Runtime/Yaml/IYamlSerializer.h>
#include <Runtime/Yaml/YamlSerializerAttribute.h>

namespace Portakal
{
	/// <summary>
	/// Domain file yaml serilizer implementation
	/// </summary>
	class PORTAKAL_API DomainFileDescriptorYamlSerializer : public IYamlSerializer
	{
		GENERATE_CLASS(DomainFileDescriptorYamlSerializer);
	public:
		DomainFileDescriptorYamlSerializer() = default;
		~DomainFileDescriptorYamlSerializer() = default;

		// Inherited via YamlSerializer
		virtual void Serialize(YAML::Emitter& emitter, const Class* pObject) override;
		virtual void Deserialize(const YAML::Node& node, Class* pObject) override;
	};

	START_GENERATE_TYPE(DomainFileDescriptorYamlSerializer);
	START_TYPE_PROPERTIES(DomainFileDescriptorYamlSerializer);
	REGISTER_TYPE_ATTRIBUTE(YamlSerializerAttribute, typeof(DomainFileDescriptor));
	REGISTER_BASE_TYPE(IYamlSerializer);
	END_TYPE_PROPERTIES;
	HAS_DEFAULT_CONSTRUCTOR(DomainFileDescriptorYamlSerializer);
	END_GENERATE_TYPE(DomainFileDescriptorYamlSerializer);
}