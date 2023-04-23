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
	mEntity->isActive(); //si instancia nula borrar, singleton
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
		SceneManager().getActiveScene()->removeEntity(mEntity->getName());
	else {
		MInstance = this;
		sceneManager().getActiveScene()->promoteToGlobal(mEntity);
		mGameState = GAMESTATE_LOADMAINMENU;
	}	
}

void GameManager::update(const double& dt)
{
	switch (mGameState)
	{
	case GameState::GAMESTATE_LOADMAINMENU:
		if (sceneManager().getScene("MainMenu") == nullptr)
			sceneManager().addScene("MainMenu");
		sceneManager().setActiveScene("MainMenu");
		sceneManager().loadEntities("mainmenu.lua");

		mGameState = GameState::GAMESTATE_MAINMENU;
		break;

	case GameState::GAMESTATE_STARTGAME:
		if (sceneManager().getScene("Race") == nullptr)
			sceneManager().addScene("Race");
		sceneManager().removeScene("MainMenu");
		sceneManager().setActiveScene("Race");
		sceneManager().loadEntities("race.lua");
		
		mGameState = GameState::GAMESTATE_INGAME;
		break;

	case GameState::GAMESTATE_LOADGAMEOVER:
		if (sceneManager().getScene("OverMenu") == nullptr)
		{
			sceneManager().addScene("OverMenu");
		}
		sceneManager().setActiveScene("OverMenu");
		sceneManager().loadEntities("overmenu.lua");
		mGameState = GameState::GAMESTATE_GAMEOVER;
		break;

	case GameState::GAMESTATE_INGAME:
		//mGameState = GAMESTATE_LOADMAINMENU;
		break;
	case GameState::GAMESTATE_MAINMENU:
	case GameState::GAMESTATE_GAMEOVER:
		//sceneManager().update();
		//processInput();
		break;
	default:
		break;
	}
}