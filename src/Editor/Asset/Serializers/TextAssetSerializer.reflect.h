#include "TextAssetSerializer.h" 
START_GENERATE_TYPE(TextAssetSerializer);
START_TYPE_PROPERTIES(TextAssetSerializer)
REGISTER_BASE_TYPE(IAssetSerializer);
REGISTER_TYPE_ATTRIBUTE(CustomAssetSerializerAttribute, "simple-text")
END_TYPE_PROPERTIES;
HAS_DEFAULT_CONSTRUCTOR(TextAssetSerializer);
END_GENERATE_TYPE(TextAssetSerializer);