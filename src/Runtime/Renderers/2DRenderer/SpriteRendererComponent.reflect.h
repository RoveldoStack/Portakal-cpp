#include "SpriteRendererComponent.h" 
START_GENERATE_TYPE(SpriteRendererComponent);
START_CLASS_TYPE_PROPERTIES(SpriteRendererComponent)
REGISTER_BASE_TYPE(Component);
REGISTER_FIELD(SpriteRendererComponent,mPosition,Vector2F,AccessSpecifier::Public);
REGISTER_FIELD(SpriteRendererComponent,mScale,Vector2F,AccessSpecifier::Public);

END_TYPE_PROPERTIES;
HAS_DEFAULT_CONSTRUCTOR(SpriteRendererComponent);
END_GENERATE_TYPE(SpriteRendererComponent);