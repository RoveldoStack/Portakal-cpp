#include "TestStruct.h" 
START_GENERATE_TYPE(TestStruct);
START_TYPE_PROPERTIES(TestStruct)
REGISTER_FIELD(TestStruct,A,int,AccessSpecifier::Public);
REGISTER_FIELD(TestStruct,B,int,AccessSpecifier::Public);
REGISTER_FIELD(TestStruct,C,int,AccessSpecifier::Public);
REGISTER_FIELD(TestStruct,MyStr,String,AccessSpecifier::Public);

END_TYPE_PROPERTIES;
HAS_DEFAULT_CONSTRUCTOR(TestStruct);
END_GENERATE_TYPE(TestStruct);