#include "EditorGameAPI.h"
#include <Runtime/World/SceneAPI.h>
namespace Portakal
{
	EditorGameState EditorGameAPI::GetCurrentState()
	{
		EditorGameAPI* pAPI = GetUnderlyingAPI();
		if (pAPI == nullptr)
			return EditorGameState::Idle;

		return pAPI->mCurrentState;
	}
	bool EditorGameAPI::StartGame()
	{
		EditorGameAPI* pAPI = GetUnderlyingAPI();
		if (pAPI == nullptr)
			return false;

		if (SceneAPI::GetPrimalScene() == nullptr) // validate if there is a primal scene
			return false;
		if (pAPI->mCurrentState != EditorGameState::Idle)
			return false;

		/*
		* Get scene descriptor from the current primal scene
		*/
		Scene* pPrimalScene = SceneAPI::GetPrimalScene();
		pPrimalScene->GenerateDescriptor(pAPI->mStartSceneDescriptor);

		/*
		* Start the current game
		*/
		pPrimalScene->SetActivationState(true);

		pAPI->mCurrentState = EditorGameState::Running;
		return true;
	}
	bool EditorGameAPI::PauseGame()
	{
		EditorGameAPI* pAPI = GetUnderlyingAPI();
		if (pAPI == nullptr)
			return false;

		if (SceneAPI::GetPrimalScene() == nullptr) // validate if there is a primal scene
			return false;

		if (pAPI->mCurrentState != EditorGameState::Running)
			return false;

		return false;
	}
	bool EditorGameAPI::Stop()
	{
		EditorGameAPI* pAPI = GetUnderlyingAPI();
		if (pAPI == nullptr)
			return false;

		if (SceneAPI::GetPrimalScene() == nullptr) // validate if there is a primal scene
			return false;

		if (pAPI->mCurrentState != EditorGameState::Running)
			return false;

		/*
		* Destroy the current scene
		*/
		Scene* pPrimalScene = SceneAPI::GetPrimalScene();
		pPrimalScene->Destroy();

		/*
		* Create and reload scene
		*/
		Scene* mStartupScene = new Scene(pAPI->mStartSceneDescriptor);

		return true;
	}
	EditorGameAPI::EditorGameAPI() :
		mCurrentState(EditorGameState::Idle)
	{

	}
	EditorGameAPI::~EditorGameAPI()
	{

	}
	
	
}