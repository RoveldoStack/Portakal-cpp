#include "TaggedObject.h"
#include <Runtime/Object/GarbageCollector.h>

namespace Portakal
{
	void TaggedObject::Destroy()
	{
		/*
		* Validate if destroyed
		*/
		if (mDestroyed)
			return;

		/*
		* Call destroy implementation
		*/
		mDestroyed = true;
		DestroyCore();

		/*
		* Register it to the garbage collector
		*/
		GarbageCollector::_Register(this);
	}
}