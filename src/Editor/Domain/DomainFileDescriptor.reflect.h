#include "DomainFileDescriptor.h" 
START_GENERATE_TYPE(DomainFileDescriptor);
START_STRUCT_TYPE_PROPERTIES(DomainFileDescriptor)
REGISTER_FIELD(DomainFileDescriptor,ResourceType,String,AccessSpecifier::Public);
REGISTER_FIELD(DomainFileDescriptor,SourceFile,String,AccessSpecifier::Public);
REGISTER_FIELD(DomainFileDescriptor,ID,Guid,AccessSpecifier::Public);

END_TYPE_PROPERTIES;
HAS_DEFAULT_CONSTRUCTOR(DomainFileDescriptor);
END_GENERATE_TYPE(DomainFileDescriptor);