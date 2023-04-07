#include "ShaderAssetSerializer.h" 
START_GENERATE_TYPE(ShaderAssetSerializer);
START_TYPE_PROPERTIES(ShaderAssetSerializer)
REGISTER_BASE_TYPE(IAssetSerializer);
REGISTER_TYPE_ATTRIBUTE(CustomAssetSerializerAttribute, "shader")
END_TYPE_PROPERTIES;
HAS_DEFAULT_CONSTRUCTOR(ShaderAssetSerializer);
END_GENERATE_TYPE(ShaderAssetSerializer);
