#include "SceneResourceEntry.h" 
START_GENERATE_TYPE(SceneResourceEntry);
START_STRUCT_TYPE_PROPERTIES(SceneResourceEntry)
REGISTER_FIELD(SceneResourceEntry,ID,Guid,AccessSpecifier::Public);

END_TYPE_PROPERTIES;
HAS_DEFAULT_CONSTRUCTOR(SceneResourceEntry);
END_GENERATE_TYPE(SceneResourceEntry);