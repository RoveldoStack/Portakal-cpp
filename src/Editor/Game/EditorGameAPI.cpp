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

		return sAPI->_StartGame();
	}
	bool EditorGameAPI::PauseGame()
	{
		if (sAPI == nullptr)
			return false;

		return sAPI->_PauseGame();
	}
	bool EditorGameAPI::Stop()
	{
		if (sAPI == nullptr)
			return false;

		return sAPI->_StopGame();
	}
	EditorGameAPI::EditorGameAPI() :
		mCurrentState(EditorGameState::Idle)
	{

	}
	EditorGameAPI::~EditorGameAPI()
	{
		sAPI = nullptr;
	}
	bool EditorGameAPI::_StartGame()
	{
		if (SceneAPI::GetPrimalScene() == nullptr) // validate if there is a primal scene
			return false;
		if (mCurrentState != EditorGameState::Idle)
			return false;

		/*
		* Get scene descriptor from the current primal scene
		*/
		Scene* pPrimalScene = SceneAPI::GetPrimalScene();
		pPrimalScene->GenerateDescriptor(sAPI->mStartSceneDescriptor);

		/*
		* Start the current game
		*/
		pPrimalScene->SetActivationState(true);

		mCurrentState = EditorGameState::Running;
		return true;
	}
	bool EditorGameAPI::_PauseGame()
	{
		if (SceneAPI::GetPrimalScene() == nullptr) // validate if there is a primal scene
			return false;

		if (mCurrentState != EditorGameState::Running)
			return false;

		return false;
	}
	bool EditorGameAPI::_StopGame()
	{
		if (SceneAPI::GetPrimalScene() == nullptr) // validate if there is a primal scene
			return false;

		if (mCurrentState != EditorGameState::Running)
			return false;

		/*
		* Destroy the current scene
		*/
		Scene* pPrimalScene = SceneAPI::GetPrimalScene();
		pPrimalScene->Destroy();

		/*
		* Create and reload scene
		*/
		Scene* mStartupScene = new Scene(mStartSceneDescriptor);

		return true;
	}
}