#include "Guid.h" 
START_GENERATE_TYPE(Guid);
START_STRUCT_TYPE_PROPERTIES(Guid)
REGISTER_FIELD(Guid,A,UInt,AccessSpecifier::Public);
REGISTER_FIELD(Guid,B,UInt,AccessSpecifier::Public);
REGISTER_FIELD(Guid,C,UInt,AccessSpecifier::Public);
REGISTER_FIELD(Guid,D,UInt,AccessSpecifier::Public);

END_TYPE_PROPERTIES;
HAS_DEFAULT_CONSTRUCTOR(Guid);
END_GENERATE_TYPE(Guid);