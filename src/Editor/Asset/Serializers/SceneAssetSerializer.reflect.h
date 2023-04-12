#include "SceneAssetSerializer.h" 
START_GENERATE_TYPE(SceneAssetSerializer);
START_TYPE_PROPERTIES(SceneAssetSerializer)
REGISTER_BASE_TYPE(IAssetSerializer);
REGISTER_TYPE_ATTRIBUTE(CustomAssetSerializerAttribute, "scene")
END_TYPE_PROPERTIES;
HAS_DEFAULT_CONSTRUCTOR(SceneAssetSerializer);
END_GENERATE_TYPE(SceneAssetSerializer);