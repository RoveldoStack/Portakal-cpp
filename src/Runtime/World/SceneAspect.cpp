#include "SceneAspect.h"
#include <Runtime/World/Component.h>

namespace Portakal
{
	void SceneAspect::_Initialize()
	{
		/*
		* Call initialize implementation
		*/
		InitializeCore();
	}
	void SceneAspect::_Execute()
	{

	}
	void SceneAspect::_Finalize()
	{
		/*
		* Call finalize implementation
		*/
		FinalizeCore();

		/*
		* Report to registered components that this aspect is removed
		*/
		for (unsigned int i = 0; i < mRegisteredComponents.GetCursor(); i++)
			mRegisteredComponents[i]->OnAspectRemoved(this);

		/*
		* Clear the component
		*/
		mRegisteredComponents.Clear();
	}
	void SceneAspect::RegisterComponent(Component* pComponent)
	{
		if (RegisterComponentCore(pComponent))
		{
			mRegisteredComponents.Add(pComponent);
		}
	}
	void SceneAspect::RemoveComponent(Component* pComponent)
	{
		mRegisteredComponents.Remove(pComponent);
	}
}