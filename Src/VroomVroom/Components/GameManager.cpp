#include "GameManager.h"

#include "EntityComponent/Entity.h"
#include "MotorEngine/Scene.h"
#include "MotorEngine/SceneManager.h"
#include "Audio/SoundManager.h"
#include "Input/InputManager.h"
#include "Render/UIComponents/UIText.h"

using namespace me;
using namespace VroomVroom;

GameManager* GameManager::MInstance = nullptr;

GameManager::GameManager() {

}

int GameManager::getContPowerUps() {
	return mContPowerUps;
}

void GameManager::addPowerUp()
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

GameManager* GameManager::Instance()
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
	}
	else if (newScene == "racetwo.lua") {
		mContPowerUps = 0;
		mNumPlayer = 2;
		mGameState = GAMESTATE_INGAME;
	}
	else if (newScene == "results.lua" || newScene == "resultstwo.lua")
		mGameState = GAMESTATE_RESULTS;
}

void GameManager::update(const double& dt)
{
	switch (mGameState)
	{
	case GameState::GAMESTATE_INGAME:
		if (inputManager().getButton("CLOSE")) {
			soundManager().stopEverySound();
			sceneManager().change("mainmenu.lua");
			mGameState = GAMESTATE_MAINMENU;
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

void GameManager::setLoserTime(std::string loserTime)
{
	mLoserTime = loserTime;
}

void GameManager::setWinnerTime(std::string winnerTime, int winner)
{
	mWinner = winner;
	mWinnerTime = winnerTime;
}
