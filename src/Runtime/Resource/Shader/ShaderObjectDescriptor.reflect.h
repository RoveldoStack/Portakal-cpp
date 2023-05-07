#include "ShaderObjectDescriptor.h" 
START_GENERATE_TYPE(ShaderObjectDescriptor);
START_STRUCT_TYPE_PROPERTIES(ShaderObjectDescriptor)
REGISTER_FIELD(ShaderObjectDescriptor,Source,String,AccessSpecifier::Public);
REGISTER_FIELD(ShaderObjectDescriptor,EntryPoint,String,AccessSpecifier::Public);
REGISTER_FIELD(ShaderObjectDescriptor,Stage,ShaderStage,AccessSpecifier::Public);

END_TYPE_PROPERTIES;
HAS_DEFAULT_CONSTRUCTOR(ShaderObjectDescriptor);
END_GENERATE_TYPE(ShaderObjectDescriptor);