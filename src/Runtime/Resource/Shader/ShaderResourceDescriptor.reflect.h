#include "ShaderResourceDescriptor.h" 
START_GENERATE_TYPE(ShaderResourceDescriptor);
START_STRUCT_TYPE_PROPERTIES(ShaderResourceDescriptor)
REGISTER_FIELD(ShaderResourceDescriptor,Source,String,AccessSpecifier::Public);
REGISTER_FIELD(ShaderResourceDescriptor,EntryPoint,String,AccessSpecifier::Public);
REGISTER_FIELD(ShaderResourceDescriptor,Stage,ShaderStage,AccessSpecifier::Public);

END_TYPE_PROPERTIES;
HAS_DEFAULT_CONSTRUCTOR(ShaderResourceDescriptor);
END_GENERATE_TYPE(ShaderResourceDescriptor);