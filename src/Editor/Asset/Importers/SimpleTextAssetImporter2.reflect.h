#include "SimpleTextAssetImporter2.h" 
START_GENERATE_TYPE(SimpleTextAssetImporter2);
START_TYPE_PROPERTIES(SimpleTextAssetImporter2)
REGISTER_BASE_TYPE(IAssetImporter);
REGISTER_TYPE_ATTRIBUTE(CustomAssetImporterAttribute, "simple_text", { ".txt",".docx" })
END_TYPE_PROPERTIES;
HAS_DEFAULT_CONSTRUCTOR(SimpleTextAssetImporter2);
END_GENERATE_TYPE(SimpleTextAssetImporter2);
