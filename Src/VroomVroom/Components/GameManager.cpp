#include "GameManager.h"
#include "EntityComponent/Entity.h"
#include "EntityComponent/Scene.h"
#include "EntityComponent/SceneManager.h"
#include "CameraFollow.h"
#include "CircuitoInfo.h"


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
	
	case me::GameState::LoadMainMenu:
		if (sceneManager().getScene("MainMenu") == nullptr)
		{
			sceneManager().addScene("MainMenu");

		}
		sceneManager().setActiveScene("MainMenu");
		sceneManager().loadEntities("mainmenu.lua");
		mGameState = GameState::MainMenu;
		break;

	case me::GameState::StartGame:
		if (sceneManager().getScene("Race") == nullptr)
		{
			sceneManager().addScene("Race");
		}
		sceneManager().setActiveScene("Race");
		sceneManager().loadEntities("race.lua");
		setEntitiesInfo();
		createPowerUps();
		mGameState = GameState::InGame;
		break;

	case me::GameState::LoadGameOver:
		if (sceneManager().getScene("OverMenu") == nullptr)
		{
			sceneManager().addScene("OverMenu");
		}
		sceneManager().setActiveScene("OverMenu");
		sceneManager().loadEntities("overmenu.lua");
		mGameState = GameState::GameOver;
		break;

	case me::GameState::MainMenu:
	case me::GameState::InGame:
	case me::GameState::GameOver:
		sceneManager().update();
		break;
	default:
		break;
	}

	
}
void me::GameManager::createPowerUps()
{
	CircuitoInfo* circuitoInfo = mCircuito->getComponent<CircuitoInfo>("circuitoinfo");
	Entity* ent;
	for (int i = 0; i < 3; i++)
	{
		Vector3 pos = circuitoInfo->getRandomPosInside();
		//ent = new Entity()
	}
}


void me::GameManager::startGame(NumPlayer num)
{
	mNumPlayer = num;
	mGameState = GameState::StartGame;
}

void me::GameManager::mainMenu()
{
	mGameState = GameState::LoadMainMenu;
}

