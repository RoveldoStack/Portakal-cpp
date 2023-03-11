#include "EditorGameAPI.h"
#include <Runtime/World/SceneAPI.h>
namespace Portakal
{
	EditorGameAPI* EditorGameAPI::sAPI = nullptr;


	EditorGameState EditorGameAPI::GetCurrentState()
	{
		if (sAPI == nullptr)
			return EditorGameState::Idle;

		return sAPI->mCurrentState;
	}
	bool EditorGameAPI::StartGame()
	{
		if (sAPI == nullptr)
			return false;
		if (SceneAPI::GetPrimalScene() == nullptr) // validate if there is a primal scene
			return false;
		if (sAPI->mCurrentState != EditorGameState::Idle)
			return false;

		/*
		* Get scene descriptor from the current primal scene
		*/
		Scene* pPrimalScene = SceneAPI::GetPrimalScene();
		pPrimalScene->GenerateDescriptor(sAPI->mStartSceneDescriptor);

		/*
		* Start the current game
		*/
		sAPI->mCurrentState = EditorGameState::Running;
		pPrimalScene->SetActivationState(true);

		return true;
	}
	bool EditorGameAPI::PauseGame()
	{
		if (sAPI == nullptr)
			return false;
		if (SceneAPI::GetPrimalScene() == nullptr) // validate if there is a primal scene
			return false;
		if (sAPI->mCurrentState != EditorGameState::Running)
			return false;

		return false;
	}
	bool EditorGameAPI::Stop()
	{
		if (sAPI == nullptr)
			return false;
		if (SceneAPI::GetPrimalScene() == nullptr) // validate if there is a primal scene
			return false;
		if (sAPI->mCurrentState != EditorGameState::Running)
			return false;

		/*
		* Get current primal scene
		*/
		Scene* pPrimalScene = SceneAPI::GetPrimalScene();
		pPrimalScene->SetActivationState(false);

		return false;
	}
	EditorGameAPI::EditorGameAPI() :
		mCurrentState(EditorGameState::Idle)
	{

	}
	EditorGameAPI::~EditorGameAPI()
	{
		sAPI = nullptr;
	}
}