#pragma once
#include <Runtime/Core/Core.h>
#include <Runtime/Reflection/Reflection.h>

namespace Portakal
{
	class Component;

	/// <summary>
	/// Scene aspect is used to populate scene property types
	/// </summary>
	PCLASS();
	class PORTAKAL_API SceneAspect : public Class
	{
		GENERATE_CLASS(SceneAspect,Virtual);

		friend class Scene;
		friend class SceneModule;
	public:
		/// <summary>
		/// Returns the owner scene
		/// </summary>
		/// <returns></returns>
		FORCEINLINE Scene* GetOwnerScene() const noexcept { return mOwnerScene; }

	protected:
		/// <summary>
		/// Called on first initialization
		/// </summary>
		virtual void Initialize() = 0;
		/// <summary>
		/// Called upon every frame
		/// </summary>
		virtual void Execute() = 0;
		/// <summary>
		/// Called upon finalization
		/// </summary>
		virtual void Finalize() = 0;
	private:
		/// <summary>
		/// Internal setter for the owner scene
		/// </summary>
		/// <param name="pScene"></param>
		void _SetOnwerScene(Scene* pScene) { mOwnerScene = pScene; }
	private:
		Scene* mOwnerScene;
	};

#include "SceneAspect.reflect.h"
}