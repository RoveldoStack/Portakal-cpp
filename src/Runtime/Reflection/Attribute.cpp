#include "Attribute.h"
#include <Runtime/Reflection/Type.h>

namespace Portakal
{
	AttributeDispatcher::AttributeDispatcher(Attribute* pAttribute, Type* pType)
	{
		Type* pAttributeType = pAttribute->GetType();
		pType->_RegisterAttribute(pAttribute);
	}
}