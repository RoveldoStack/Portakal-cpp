#include "EditorWindowSettings.h" 
START_GENERATE_TYPE(EditorWindowSettings);
START_TYPE_PROPERTIES(EditorWindowSettings)
REGISTER_ARRAY_FIELD(EditorWindowSettings, Windows, EditorWindowSetting);
END_TYPE_PROPERTIES;
HAS_DEFAULT_CONSTRUCTOR(EditorWindowSettings);
END_GENERATE_TYPE(EditorWindowSettings);