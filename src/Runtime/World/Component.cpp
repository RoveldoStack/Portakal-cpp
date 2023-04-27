#include "Component.h"
#include <Runtime/World/Entity.h>

namespace Portakal
{
	void Component::DestroyCore()
	{
		/*
		* Notify entity
		*/
		mOwnerEntity->_NotifyComponentDeleted(this);
	}
}