#include "MaterialSerializer.h" 
START_GENERATE_TYPE(MaterialSerializer);
START_CLASS_TYPE_PROPERTIES(MaterialSerializer)
REGISTER_BASE_TYPE(IResourceSerializer);
REGISTER_TYPE_ATTRIBUTE(CustomResourceSerializerAttribute,"material"))
END_TYPE_PROPERTIES;
HAS_DEFAULT_CONSTRUCTOR(MaterialSerializer);
END_GENERATE_TYPE(MaterialSerializer);