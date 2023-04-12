#include "TextureSerializer.h" 
START_GENERATE_TYPE(TextureSerializer);
START_TYPE_PROPERTIES(TextureSerializer)
REGISTER_BASE_TYPE(IResourceSerializer);
REGISTER_TYPE_ATTRIBUTE(CustomResourceSerializerAttribute, "texture")
END_TYPE_PROPERTIES;
HAS_DEFAULT_CONSTRUCTOR(TextureSerializer);
END_GENERATE_TYPE(TextureSerializer);