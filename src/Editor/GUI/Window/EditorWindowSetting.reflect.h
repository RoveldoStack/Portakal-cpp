#include "EditorWindowSetting.h" 
START_GENERATE_TYPE(EditorWindowSetting);
START_STRUCT_TYPE_PROPERTIES(EditorWindowSetting)
REGISTER_FIELD(EditorWindowSetting,Name,String,AccessSpecifier::Public);
REGISTER_FIELD(EditorWindowSetting,ID,Guid,AccessSpecifier::Public);
REGISTER_FIELD(EditorWindowSetting,DockState,EditorWindowDockState,AccessSpecifier::Public);
REGISTER_FIELD(EditorWindowSetting,OwnerID,Guid,AccessSpecifier::Public);

END_TYPE_PROPERTIES;
HAS_DEFAULT_CONSTRUCTOR(EditorWindowSetting);
END_GENERATE_TYPE(EditorWindowSetting);