#include "TextureAssetSerializer.h" 
START_GENERATE_TYPE(TextureAssetSerializer);
START_TYPE_PROPERTIES(TextureAssetSerializer)
REGISTER_BASE_TYPE(IAssetSerializer);
REGISTER_TYPE_ATTRIBUTE(CustomAssetSerializerAttribute, "texture")
END_TYPE_PROPERTIES;
HAS_DEFAULT_CONSTRUCTOR(TextureAssetSerializer);
END_GENERATE_TYPE(TextureAssetSerializer);
