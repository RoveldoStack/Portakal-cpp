#pragma once
#include <Runtime/Containers/Array.h>

namespace Portakal
{
	struct SceneDescriptor;
	class Scene;

	class PORTAKAL_API SceneAPI
	{
		friend class SceneModule;
		static SceneAPI* _api;
	public:
		static Scene* GetPrimalScene();
		static Array<Scene*> GetScenes();
		static Scene* CreateScene(const bool bMarkPrimal);
		static Scene* CreateScene(const SceneDescriptor& descriptor,const bool bMarkPrimal);
		static void MarkScenePrimal(Scene* pScene);
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