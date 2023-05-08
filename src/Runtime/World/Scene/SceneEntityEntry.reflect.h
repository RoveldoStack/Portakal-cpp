#include "SceneEntityEntry.h" 
START_GENERATE_TYPE(SceneEntityEntry);
START_STRUCT_TYPE_PROPERTIES(SceneEntityEntry)
REGISTER_FIELD(SceneEntityEntry,TagName,String,AccessSpecifier::Public);
REGISTER_FIELD(SceneEntityEntry,ID,Guid,AccessSpecifier::Public);
REGISTER_ARRAY_FIELD(SceneEntityEntry,Components,SceneComponentEntry,AccessSpecifier::Public);

END_TYPE_PROPERTIES;
HAS_DEFAULT_CONSTRUCTOR(SceneEntityEntry);
END_GENERATE_TYPE(SceneEntityEntry);