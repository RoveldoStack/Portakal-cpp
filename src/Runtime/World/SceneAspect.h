#pragma once
#include <Runtime/Core/Core.h>
#include <Runtime/Reflection/Reflection.h>

namespace Portakal
{
	/// <summary>
	/// Scene aspect is used to populate scene property types
	/// </summary>
	class PORTAKAL_API SceneAspect : public Class
	{
		GENERATE_CLASS(SceneAspect);

		friend class Scene;
	public:
		/// <summary>
		/// Returns the owner scene
		/// </summary>
		/// <returns></returns>
		FORCEINLINE Scene* GetOwnerScene() const noexcept { return mOwnerScene; }

		/// <summary>
		/// Called on first initialization
		/// </summary>
		virtual void OnInitialize() = 0;

		/// <summary>
		/// Called upon every frame
		/// </summary>
		virtual void OnExecute() = 0;

		/// <summary>
		/// Called upon finalization
		/// </summary>
		virtual void OnFinalize() = 0;
	private:

		/// <summary>
		/// Internal setter for the owner scene
		/// </summary>
		/// <param name="pScene"></param>
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