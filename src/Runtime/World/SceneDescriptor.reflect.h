#include "SceneDescriptor.h" 
START_GENERATE_TYPE(SceneDescriptor);
START_STRUCT_TYPE_PROPERTIES(SceneDescriptor)
REGISTER_ARRAY_FIELD(SceneDescriptor,Resources,SceneResourceEntry,AccessSpecifier::Public);
REGISTER_ARRAY_FIELD(SceneDescriptor,Aspects,SceneAspectEntry,AccessSpecifier::Public);
REGISTER_ARRAY_FIELD(SceneDescriptor,Entities,SceneEntityEntry,AccessSpecifier::Public);

END_TYPE_PROPERTIES;
HAS_DEFAULT_CONSTRUCTOR(SceneDescriptor);
END_GENERATE_TYPE(SceneDescriptor);