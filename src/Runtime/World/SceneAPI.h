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
	public:
		FORCEINLINE static Scene* GetPrimalScene();
		FORCEINLINE static Array<Scene*> GetScenes();
		static void RegisterScene(Scene* pScene);
		static void RemoveScene(Scene* pScene);
		static void ReportPrimal(Scene* pScene);
	private:
		static Array<Scene*> sScenes;
		static Scene* sPrimalScene;
	private:
		SceneAPI() = delete;
		~SceneAPI() = delete;
	};
}