#include "ShaderAuthoringTool.h" 
START_GENERATE_TYPE(ShaderAuthoringTool);
START_TYPE_PROPERTIES(ShaderAuthoringTool)
REGISTER_BASE_TYPE(IAssetAuthoringTool);
REGISTER_TYPE_ATTRIBUTE(CustomAssetAuthoringToolAttribute, "shader")
END_TYPE_PROPERTIES;
HAS_DEFAULT_CONSTRUCTOR(ShaderAuthoringTool);
END_GENERATE_TYPE(ShaderAuthoringTool);