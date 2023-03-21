#include "GameManager.h"
#include "EntityComponent/Entity.h"
#include "EntityComponent/Scene.h"
#include "EntityComponent/SceneManager.h"
#include "CameraFollow.h"


me::GameManager::~GameManager()
{
}

void me::GameManager::start()
{

}

void me::GameManager::setEntitiesInfo()
{

	mPlayerOne = sceneManager().getActiveScene().get()->findEntity("playerOne").get();
	
	if (mNumPlayer == NumPlayer::TwoPlayer)
	{
		mPlayerTwo = sceneManager().getActiveScene().get()->findEntity("playerTwo").get();
		
	}

	mCircuito = sceneManager().getActiveScene().get()->findEntity("circuito").get();
	mMeta = sceneManager().getActiveScene().get()->findEntity("meta").get();

	
}

void me::GameManager::update()
{
	switch (mGameState)
	{
	case me::GameState::MainMenu:
		sceneManager().addScene("MainMenu");
		sceneManager().setActiveScene("MainMenu");
		sceneManager().loadEntities("mainmenu.lua");

		break;
	case me::GameState::StartGame:
		sceneManager().addScene("Race");
		sceneManager().setActiveScene("Race");
		sceneManager().loadEntities("race.lua");
		setEntitiesInfo();
		createPowerUps();
		mGameState = GameState::InGame;
		break;
	case me::GameState::InGame:
		
		break;
	case me::GameState::GameOver:
		sceneManager().addScene("OverMenu");
		sceneManager().setActiveScene("OverMenu");
		sceneManager().loadEntities("overmenu.lua");
		break;
	default:
		break;
	}

	sceneManager().update();
}
void me::GameManager::createPowerUps()
{
	
}


void me::GameManager::startGame(NumPlayer num)
{
	mNumPlayer = num;
	mGameState = GameState::StartGame;
}

void me::GameManager::mainMenu()
{
	mGameState = GameState::MainMenu;
}

