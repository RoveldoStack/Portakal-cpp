#pragma once
#include <Runtime/World/SceneAspect.h>

namespace Portakal
{
	PCLASS();
	class PORTAKAL_API Renderer2DSceneAspect : public SceneAspect
	{
		GENERATE_CLASS(Renderer2DSceneAspect);
	public:
		Renderer2DSceneAspect() = default;
		~Renderer2DSceneAspect() = default;
	private:
		// Inherited via SceneAspect
		virtual void InitializeCore() override;
		virtual void ExecuteCore() override;
		virtual void FinalizeCore() override;
	private:

		// Inherited via SceneAspect
		virtual bool RegisterComponentCore(Component* pComponent) override;
		virtual void RemoveComponentCore(Component* pComponent) override;
	};

#include "Renderer2DSceneAspect.reflect.h"
}