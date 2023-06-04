#include "Renderer2DSceneAspect.h"
#include <Runtime/Renderers/2DRenderer/SpriteCameraComponent.h>
#include <Runtime/Renderers/2DRenderer/SpriteRendererComponent.h>

namespace Portakal
{
	void Renderer2DSceneAspect::InitializeCore()
	{

	}
	void Renderer2DSceneAspect::ExecuteCore()
	{

	}
	void Renderer2DSceneAspect::FinalizeCore()
	{

	}
	bool Renderer2DSceneAspect::RegisterComponentCore(Component* pComponent)
	{
		if (pComponent->GetType() == typeof(SpriteRendererComponent))
		{
			return true;
		}
		else if (pComponent->GetType() == typeof(SpriteCameraComponent))
		{
			return true;
		}

		return false;
	}
	void Renderer2DSceneAspect::RemoveComponentCore(Component* pComponent)
	{
	}
}