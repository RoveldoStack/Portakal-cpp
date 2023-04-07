#include "SimpleTextAssetImporter.h" 
START_GENERATE_TYPE(SimpleTextAssetImporter);
START_TYPE_PROPERTIES(SimpleTextAssetImporter)
REGISTER_BASE_TYPE(IAssetImporter);
REGISTER_TYPE_ATTRIBUTE(CustomAssetImporterAttribute, "simple_text", { ".txt",".docx" })
END_TYPE_PROPERTIES;
HAS_DEFAULT_CONSTRUCTOR(SimpleTextAssetImporter);
END_GENERATE_TYPE(SimpleTextAssetImporter);
