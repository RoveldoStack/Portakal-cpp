#include "ShaderSerializer.h" 
START_GENERATE_TYPE(ShaderSerializer);
START_CLASS_TYPE_PROPERTIES(ShaderSerializer)
REGISTER_BASE_TYPE(IResourceSerializer);
REGISTER_TYPE_ATTRIBUTE(CustomResourceSerializerAttribute, "shader")
END_TYPE_PROPERTIES;
HAS_DEFAULT_CONSTRUCTOR(ShaderSerializer);
END_GENERATE_TYPE(ShaderSerializer);