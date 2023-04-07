#include "DomainFileDescriptorYamlSerializer.h" 
START_GENERATE_TYPE(DomainFileDescriptorYamlSerializer);
START_TYPE_PROPERTIES(DomainFileDescriptorYamlSerializer)
REGISTER_BASE_TYPE(IYamlSerializer);
REGISTER_TYPE_ATTRIBUTE(YamlSerializerAttribute, typeof(DomainFileDescriptor))
END_TYPE_PROPERTIES;
HAS_DEFAULT_CONSTRUCTOR(DomainFileDescriptorYamlSerializer);
END_GENERATE_TYPE(DomainFileDescriptorYamlSerializer);
