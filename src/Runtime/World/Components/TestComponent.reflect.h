#include "TestComponent.h" 
START_GENERATE_TYPE(TestComponent);
START_TYPE_PROPERTIES(TestComponent)
REGISTER_BASE_TYPE(Component);
REGISTER_FIELD(TestComponent,int0,int,AccessSpecifier::Public);
REGISTER_FIELD(TestComponent,int1,int,AccessSpecifier::Public);
REGISTER_FIELD(TestComponent,int3,int,AccessSpecifier::Public);

END_TYPE_PROPERTIES;
HAS_DEFAULT_CONSTRUCTOR(TestComponent);
END_GENERATE_TYPE(TestComponent);
