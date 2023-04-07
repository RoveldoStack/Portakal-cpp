#include "TextureAuthoringTool.h" 
START_GENERATE_TYPE(TextureAuthoringTool);
START_TYPE_PROPERTIES(TextureAuthoringTool)
REGISTER_BASE_TYPE(IAssetAuthoringTool);
REGISTER_TYPE_ATTRIBUTE(CustomAssetAuthoringToolAttribute, "texture")
END_TYPE_PROPERTIES;
HAS_DEFAULT_CONSTRUCTOR(TextureAuthoringTool);
END_GENERATE_TYPE(TextureAuthoringTool);
