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

		/// <summary>
		/// Registers anew component
		/// </summary>
		/// <param name="pComponent"></param>
		void RegisterComponent(Component* pComponent);

		/*
		* Removes existing component
		*/
		void RemoveComponent(Component* pComponent);
	protected:
		virtual void InitializeCore() = 0;
		virtual void ExecuteCore() = 0;
		virtual void FinalizeCore() = 0;
		virtual bool RegisterComponentCore(Component* pComponent) = 0;
		virtual void RemoveComponentCore(Component* pComponent) = 0;
	private:
		/// <summary>
		/// Called on first initialization
		/// </summary>
		void _Initialize();
		/// <summary>
		/// Called upon every frame
		/// </summary>
		void _Execute();
		/// <summary>
		/// Called upon finalization
		/// </summary>
		void _Finalize();

		/// <summary>
		/// Internal setter for the owner scene
		/// </summary>
		/// <param name="pScene"></param>
		void _SetOnwerScene(Scene* pScene) { mOwnerScene = pScene; }
	private:
		Scene* mOwnerScene;
		Array<Component*> mRegisteredComponents;
	};

#include "SceneAspect.reflect.h"
}