#include "SceneSerializer.h" 
START_GENERATE_TYPE(SceneSerializer);
START_TYPE_PROPERTIES(SceneSerializer)
REGISTER_BASE_TYPE(IResourceSerializer);
REGISTER_TYPE_ATTRIBUTE(CustomResourceSerializerAttribute, "scene")
END_TYPE_PROPERTIES;
HAS_DEFAULT_CONSTRUCTOR(SceneSerializer);
END_GENERATE_TYPE(SceneSerializer);
