#pragma once
#include <Runtime/Containers/Array.h>

namespace Portakal
{
	struct SceneDescriptor;
	class Scene;

	/// <summary>
	/// API for enabling the scene operations across the application
	/// </summary>
	class PORTAKAL_API SceneAPI
	{
		friend class SceneModule;

		static SceneAPI* sAPI;
	public:

		/// <summary>
		/// Returns the primal scene
		/// </summary>
		/// <returns></returns>
		static Scene* GetPrimalScene();

		/// <summary>
		/// Returns all the scenes
		/// </summary>
		/// <returns></returns>
		static Array<Scene*> GetScenes();

		/// <summary>
		/// Creates a scene
		/// </summary>
		/// <param name="bMarkPrimal"></param>
		/// <returns></returns>
		static Scene* CreateScene(const bool bMarkPrimal);

		/// <summary>
		/// Creates a scene via descriptor
		/// </summary>
		/// <param name="descriptor"></param>
		/// <param name="bMarkPrimal"></param>
		/// <returns></returns>
		static Scene* CreateScene(const SceneDescriptor& descriptor,const bool bMarkPrimal);

		/// <summary>
		/// Marks a scene primal
		/// </summary>
		/// <param name="pScene"></param>
		static void MarkScenePrimal(Scene* pScene);

		/// <summary>
		/// Deletes the existing scene
		/// </summary>
		/// <param name="pScene"></param>
		static void DeleteScene(Scene* pScene);

	public:
		Scene* CreateSceneInternal(const bool bMarkPrimal);
		Scene* CreateSceneInternal(const SceneDescriptor& descriptor, const bool bMarkPrimal);
		void MarkScenePrimalInternal(Scene* pScene);
		void DeleteSceneInternal(Scene* pScene);

	private:
		SceneAPI();
		~SceneAPI();

		void RegisterTargetScene(Scene* pScene, const bool bMarkPrimal);
	private:
		Array<Scene*> mScenes;
		Scene* mPrimalScene;

	};
}