#include "GameManager.h"

#include "EntityComponent/Entity.h"
#include "EntityComponent/Scene.h"
#include "EntityComponent/SceneManager.h"
#include "EntityComponent/Components/Transform.h"
#include "EntityComponent/Components/ParticleSystem.h"
#include "Input/InputManager.h"
#include "EntityComponent/Components/UIText.h"

#include "VehicleController.h"
#include "CameraFollow.h"

#include <iostream>

using namespace me;
using namespace VroomVroom;

GameManager* GameManager::MInstance = nullptr;

GameManager::GameManager() {

}

int VroomVroom::GameManager::getContPowerUps() {
	return mContPowerUps;
}

void VroomVroom::GameManager::addPowerUp()
{
	mContPowerUps++;
}

int GameManager::getNumPlayer()
{
	return mNumPlayer;
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
	else if (newScene == "race.lua" ) {
		mContPowerUps = 0;
		mNumPlayer = 1;
		mGameState = GAMESTATE_INGAME;
		std::cout << newScene << std::endl;

	}
	else if (newScene == "racetwo.lua") {
		mContPowerUps = 0;
		mNumPlayer = 2;
		mGameState = GAMESTATE_INGAME;
		std::cout << newScene << std::endl;
	}
	else if (newScene == "results.lua" || newScene == "resultstwo.lua")
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
		break;
	case GameState::GAMESTATE_RESULTS:
		if (sceneManager().getActiveScene()->getName() == "results.lua" || sceneManager().getActiveScene()->getName() == "resultstwo.lua") {
			if (mNumPlayer>1) {
				if (mWinner == 0) {

					sceneManager().getActiveScene()->findEntity("caronetext")->getComponent<UIText>("uitext")->setText(mWinnerTime);
					sceneManager().getActiveScene()->findEntity("cartwotext")->getComponent<UIText>("uitext")->setText(mLoserTime);
				}
				else {
					sceneManager().getActiveScene()->findEntity("caronetext")->getComponent<UIText>("uitext")->setText(mLoserTime);
					sceneManager().getActiveScene()->findEntity("cartwotext")->getComponent<UIText>("uitext")->setText(mWinnerTime);
				}
			}
			else {
				sceneManager().getActiveScene()->findEntity("caronetext")->getComponent<UIText>("uitext")->setText(mWinnerTime);
			}
		}
		break;
	default:
		break;
	}
}

void VroomVroom::GameManager::setLoserTime(std::string loserTime)
{
	mLoserTime = loserTime;
}

void VroomVroom::GameManager::setWinnerTime(std::string winnerTime, int winner)
{
	mWinner = winner;
	mWinnerTime = winnerTime;
}
