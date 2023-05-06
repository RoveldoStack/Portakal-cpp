#pragma once
#include <Runtime/Core/Core.h>
#include <Runtime/World/Scene.h>
#include <Editor/Game/EditorGameState.h>
#include <Runtime/Object/API.h>

namespace Portakal
{
	class Scene;

	/// <summary>
	/// Represents the game state of the editor
	/// </summary>
	class PORTAKAL_API EditorGameAPI : public API<EditorGameAPI>
	{
		friend class EditorGameModule;
	public:
		/// <summary>
		/// Returns the current state
		/// </summary>
		/// <returns></returns>
		FORCEINLINE static EditorGameState GetCurrentState();

		/// <summary>
		/// Starts the editor game
		/// </summary>
		/// <returns></returns>
		static bool StartGame();

		/// <summary>
		/// Pauses the editor game
		/// </summary>
		/// <returns></returns>
		static bool PauseGame();

		/// <summary>
		/// Stops the editor game
		/// </summary>
		/// <returns></returns>
		static bool Stop();
	private:
		EditorGameAPI();
		virtual ~EditorGameAPI() override;
	private:
		EditorGameState mCurrentState;
		SceneDescriptor mStartSceneDescriptor;
	};
}