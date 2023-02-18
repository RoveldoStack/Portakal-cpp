#pragma once
#include <Runtime/Core/Core.h>
#include <Runtime/Reflection/Reflection.h>

namespace Portakal
{
	class PORTAKAL_API SceneAspect : public Class
	{
		GENERATE_CLASS(SceneAspect);

		friend class Scene;
	public:
		FORCEINLINE Scene* GetOwnerScene() const noexcept { return mOwnerScene; }

		virtual void OnInitialize() = 0;
		virtual void OnExecute() = 0;
		virtual void OnFinalize() = 0;
	private:
		void _SetOnwerScene(Scene* pScene) { mOwnerScene = pScene; }
	private:
		Scene* mOwnerScene;
	};

	START_GENERATE_TYPE(SceneAspect);
		START_TYPE_PROPERTIES(SceneAspect);
		END_TYPE_PROPERTIES;
	NO_DEFAULT_CONSTRUCTOR;
	END_GENERATE_TYPE(SceneAspect);
}