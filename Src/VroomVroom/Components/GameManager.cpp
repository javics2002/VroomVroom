#include "GameManager.h"

#include "EntityComponent/Entity.h"
#include "EntityComponent/Scene.h"
#include "EntityComponent/SceneManager.h"
#include "EntityComponent/Components/Transform.h"
#include "EntityComponent/Components/ParticleSystem.h"
#include "Input/InputManager.h"

#include "VehicleController.h"
#include "CameraFollow.h"

using namespace me;
using namespace VroomVroom;

GameManager* GameManager::MInstance = nullptr;

GameManager::GameManager() {

}

GameManager::~GameManager()
{
}

GameManager* VroomVroom::GameManager::Instance()
{
	return MInstance;
}

void GameManager::start()
{
	if (MInstance != nullptr)
		sceneManager().getActiveScene()->removeEntity(mEntity->getName());
	else {
		MInstance = this;
		sceneManager().getActiveScene()->promoteToGlobal(mEntity);
		mGameState = GAMESTATE_MAINMENU;
	}	
}

void GameManager::changeState(std::string newScene) {
	if (newScene == "mainmenu.lua")
		mGameState = GAMESTATE_MAINMENU;
	else if (newScene == "race.lua")
		mGameState = GAMESTATE_INGAME;
	else if (newScene == "results.lua")
		mGameState = GAMESTATE_RESULTS;
}

void GameManager::update(const double& dt)
{
	switch (mGameState)
	{
	case GameState::GAMESTATE_INGAME:
		if (inputManager().getButton("CLOSE" + std::to_string(0))) {
			sceneManager().change("mainmenu.lua");
			mGameState = GAMESTATE_MAINMENU;
		}
		else if (inputManager().getButton("RESULTS" + std::to_string(0))) {
			sceneManager().change("results.lua");
			mGameState = GAMESTATE_RESULTS;
		}
		break;
	case GameState::GAMESTATE_MAINMENU:
	case GameState::GAMESTATE_GAMEOVER:
	case GameState::GAMESTATE_RESULTS:
		//sceneManager().update();
		//processInput();
		break;
	default:
		break;
	}
}