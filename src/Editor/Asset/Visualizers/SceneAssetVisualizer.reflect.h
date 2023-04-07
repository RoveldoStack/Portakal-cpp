#include "SceneAssetVisualizer.h" 
START_GENERATE_TYPE(SceneAssetVisualizer);
START_TYPE_PROPERTIES(SceneAssetVisualizer)
REGISTER_BASE_TYPE(IAssetVisualizer);
REGISTER_TYPE_ATTRIBUTE(CustomAssetVisualizerAttribute, "scene")
END_TYPE_PROPERTIES;
HAS_DEFAULT_CONSTRUCTOR(SceneAssetVisualizer);
END_GENERATE_TYPE(SceneAssetVisualizer);
