#include "SceneOpenOperation.h" 
START_GENERATE_TYPE(SceneOpenOperation);
START_TYPE_PROPERTIES(SceneOpenOperation)
REGISTER_BASE_TYPE(IAssetOpenOperation);
REGISTER_TYPE_ATTRIBUTE(CustomAssetOpenOperationAttribute, "scene")
END_TYPE_PROPERTIES;
HAS_DEFAULT_CONSTRUCTOR(SceneOpenOperation);
END_GENERATE_TYPE(SceneOpenOperation);