#include "Project.h" 
START_GENERATE_TYPE(Project);
START_TYPE_PROPERTIES(Project)
REGISTER_FIELD(Project,Name,String,AccessSpecifier::Public);
REGISTER_FIELD(Project,ID,Guid,AccessSpecifier::Public);
REGISTER_FIELD(Project,VersionMajor,UInt,AccessSpecifier::Public);
REGISTER_FIELD(Project,VersionMinor,UInt,AccessSpecifier::Public);
REGISTER_FIELD(Project,VersionPatch,UInt,AccessSpecifier::Public);
REGISTER_FIELD(Project,ProjectFolderAbsolutePath,String,AccessSpecifier::Public);

END_TYPE_PROPERTIES;
HAS_DEFAULT_CONSTRUCTOR(Project);
END_GENERATE_TYPE(Project);