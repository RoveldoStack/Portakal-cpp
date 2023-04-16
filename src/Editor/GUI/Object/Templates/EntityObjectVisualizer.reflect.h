#include "EntityObjectVisualizer.h" 
START_GENERATE_TYPE(EntityObjectVisualizer);
START_TYPE_PROPERTIES(EntityObjectVisualizer)
REGISTER_BASE_TYPE(EditorObjectVisualizer);
REGISTER_TYPE_ATTRIBUTE(CustomEditorObjectAttribute, typeof(Entity))
END_TYPE_PROPERTIES;
HAS_DEFAULT_CONSTRUCTOR(EntityObjectVisualizer);
END_GENERATE_TYPE(EntityObjectVisualizer);