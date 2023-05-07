#include "TextureAssetImporter.h" 
START_GENERATE_TYPE(TextureAssetImporter);
START_CLASS_TYPE_PROPERTIES(TextureAssetImporter)
REGISTER_BASE_TYPE(IAssetImporter);
REGISTER_TYPE_ATTRIBUTE(CustomAssetImporterAttribute, "texture", { ".png",".jpg",".jpeg" })
END_TYPE_PROPERTIES;
HAS_DEFAULT_CONSTRUCTOR(TextureAssetImporter);
END_GENERATE_TYPE(TextureAssetImporter);