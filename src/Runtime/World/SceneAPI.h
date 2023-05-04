#pragma once
#include <Runtime/Containers/Array.h>
#include <Runtime/Object/API.h>

namespace Portakal
{
	struct SceneDescriptor;
	class Scene;

	/// <summary>
	/// API for enabling the scene operations across the application
	/// </summary>
	class PORTAKAL_API SceneAPI : public API<SceneAPI>
	{
	public:
		FORCEINLINE static Scene* GetPrimalScene();
		FORCEINLINE static Array<Scene*> GetScenes();
		static void RegisterScene(Scene* pScene);
		static void RemoveScene(Scene* pScene);
		static void ReportPrimal(Scene* pScene);
	public:
		SceneAPI();
		virtual ~SceneAPI() override;
	private:
		Array<Scene*> mScenes;
		Scene* mPrimalScene;
	};
}