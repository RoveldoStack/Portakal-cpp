#include "SceneComponentEntry.h" 
START_GENERATE_TYPE(SceneComponentEntry);
START_STRUCT_TYPE_PROPERTIES(SceneComponentEntry)
REGISTER_FIELD(SceneComponentEntry,TypeName,String,AccessSpecifier::Public);
REGISTER_FIELD(SceneComponentEntry,TagName,String,AccessSpecifier::Public);
REGISTER_FIELD(SceneComponentEntry,ID,Guid,AccessSpecifier::Public);
REGISTER_ARRAY_FIELD(SceneComponentEntry,Fields,SceneComponentFieldEntry,AccessSpecifier::Public);

END_TYPE_PROPERTIES;
HAS_DEFAULT_CONSTRUCTOR(SceneComponentEntry);
END_GENERATE_TYPE(SceneComponentEntry);