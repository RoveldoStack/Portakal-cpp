#include "TextureAssetVisualizer.h" 
START_GENERATE_TYPE(TextureAssetVisualizer);
START_TYPE_PROPERTIES(TextureAssetVisualizer)
REGISTER_BASE_TYPE(IAssetVisualizer);
REGISTER_TYPE_ATTRIBUTE(CustomAssetVisualizerAttribute, "texture")
END_TYPE_PROPERTIES;
HAS_DEFAULT_CONSTRUCTOR(TextureAssetVisualizer);
END_GENERATE_TYPE(TextureAssetVisualizer);
