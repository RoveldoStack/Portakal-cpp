#include "ShaderAssetVisualizer.h" 
START_GENERATE_TYPE(ShaderAssetVisualizer);
START_TYPE_PROPERTIES(ShaderAssetVisualizer)
REGISTER_BASE_TYPE(IAssetVisualizer);
REGISTER_TYPE_ATTRIBUTE(CustomAssetVisualizerAttribute, "shader")
END_TYPE_PROPERTIES;
HAS_DEFAULT_CONSTRUCTOR(ShaderAssetVisualizer);
END_GENERATE_TYPE(ShaderAssetVisualizer);
