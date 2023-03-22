#include "GameManager.h"

#include "EntityComponent/Entity.h"
#include "EntityComponent/Scene.h"
#include "EntityComponent/SceneManager.h"
#include "EntityComponent/Components/Transform.h"
#include "EntityComponent/Components/ParticleSystem.h"
#include "Input/InputManager.h"

#include "VehicleController.h"
#include "CameraFollow.h"
#include "CircuitoInfo.h"



me::GameManager::~GameManager()
{
}

void me::GameManager::start()
{

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
		setPowerUps();
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

void me::GameManager::setEntitiesInfo()
{

	mPlayerOne = sceneManager().getActiveScene().get()->findEntity("playerOne").get();
	mPlayerOne->getComponent<VehicleController>("vehiclecontroller")->setInput("LEFT", "RIGHT", "JOYSTICK1", "UP", "DOWN", "ENTER");
	mPlayerOneLastCheckpointPos = mPlayerOne->getComponent<Transform>("transform")->getPosition();
	//setupInput(1);
	if (mNumPlayer == NumPlayer::TwoPlayer)
	{
		mPlayerTwo = sceneManager().getActiveScene().get()->findEntity("playerTwo").get();
		mPlayerTwo->getComponent<VehicleController>("vehiclecontroller")->setInput("A", "D", "JOYSTICK2", "W", "S", "SPACE");
		mPlayerTwoLastCheckpointPos = mPlayerOne->getComponent<Transform>("transform")->getPosition();
		//setupInput(2);
	}

	mCircuito = sceneManager().getActiveScene().get()->findEntity("circuito").get();
	mCircuitoInfo = mCircuito->getComponent<CircuitoInfo>("circuitoinfo");
	mMeta = sceneManager().getActiveScene().get()->findEntity("meta").get();

	mPowerUps["powerup1"] = sceneManager().getActiveScene().get()->findEntity("powerup1").get();
	mPowerUps["powerup2"] = sceneManager().getActiveScene().get()->findEntity("powerup2").get();
	mPowerUps["powerup3"] = sceneManager().getActiveScene().get()->findEntity("powerup3").get();
	
}

/*
void me::GameManager::setupInput(int player)
{
	if (player == 1)
	{
		//"LEFT", "RIGHT", "JOYSTICKRIGHT", "UP", "DOWN", "ENTER"
		Input left, right, joy1, up, down, enter;
		left.type = INPUTTYPE_KEYBOARD;
		left.which = SDLK_LEFT;
		inputManager().addButton("LEFT", left);

		right.type = INPUTTYPE_KEYBOARD;
		right.which = SDLK_RIGHT;
		inputManager().addButton("RIGHT", right);

		joy1.type = INPUTTYPE_GAMEPAD_AXIS;
		joy1.which = Gamepad_Left;
		inputManager().addButton("JOYSTICK1", joy1);

		if (mPlayerOneType == PlayerInputType::Keyboard)
		{
			up.type = INPUTTYPE_KEYBOARD;
			up.which = SDLK_UP;
			inputManager().addButton("UP", up);

			down.type = INPUTTYPE_KEYBOARD;
			down.which = SDLK_DOWN;
			inputManager().addButton("DOWN", down);

			enter.type = INPUTTYPE_KEYBOARD;
			enter.which = SDLK_RETURN;
			inputManager().addButton("ENTER", enter);
		}
		else
		{
			up.type = INPUTTYPE_GAMEPAD_BUTTON;
			up.which = B;
			inputManager().addButton("UP", up);

			down.type = INPUTTYPE_GAMEPAD_BUTTON;
			down.which = A;
			inputManager().addButton("DOWN", down);

			enter.type = INPUTTYPE_GAMEPAD_BUTTON;
			enter.which = X;
			inputManager().addButton("ENTER", enter);

		}
	}
	else if (player == 2)
	{
		//"A", "D", "JOYSTICK2", "W", "S", "SPACE"
		Input keya, keyd, joy2, keyw, keys, space;
		keya.type = INPUTTYPE_KEYBOARD;
		keya.which = SDLK_A;
		inputManager().addButton("A", keya);

		keyd.type = INPUTTYPE_KEYBOARD;
		keyd.which = SDLK_D;
		inputManager().addButton("D", keyw);

		joy2.type = INPUTTYPE_GAMEPAD_AXIS;
		joy2.which = Gamepad_Left;
		inputManager().addButton("JOYSTICK2", joy2);

		if (mPlayerOneType == PlayerInputType::Keyboard)
		{
			keyw.type = INPUTTYPE_KEYBOARD;
			keyw.which = SDLK_W;
			inputManager().addButton("W", keyw);

			keys.type = INPUTTYPE_KEYBOARD;
			keys.which = SDLK_S;
			inputManager().addButton("S", keys);

			space.type = INPUTTYPE_KEYBOARD;
			space.which = SDLK_SPACE;
			inputManager().addButton("SPACE", space);
		}
		else
		{
			keyw.type = INPUTTYPE_GAMEPAD_BUTTON;
			keyw.which = B;
			inputManager().addButton("W", keyw);

			keys.type = INPUTTYPE_GAMEPAD_BUTTON;
			keys.which = A;
			inputManager().addButton("S", keys);

			space.type = INPUTTYPE_GAMEPAD_BUTTON;
			space.which = X;
			inputManager().addButton("SPACE", space);

		}
	}
}
*/


void me::GameManager::setPowerUps()
{


	Vector3 pos1, pos2, pos3;
	pos1 = mCircuitoInfo->getRandomPosInside();

	//distance should be change, multiply by scale
	do {
		pos2 = mCircuitoInfo->getRandomPosInside();
	} while ((pos2 - pos1).magnitude() < 2.0f);

	do {
		pos3 = mCircuitoInfo->getRandomPosInside();
	} while ((pos3 - pos1).magnitude() < 2.0f || (pos3 -pos2).magnitude() < 2.0f);

	mPowerUps["powerup1"]->getComponent<Transform>("transform")->setPosition(pos1);
	//mPowerUps["powerup1"]->getComponent<ParticleSystem>("particlesystem")->setEmitting(true);
	mPowerUps["powerup2"]->getComponent<Transform>("transform")->setPosition(pos2);
	//mPowerUps["powerup2"]->getComponent<ParticleSystem>("particlesystem")->setEmitting(true);
	mPowerUps["powerup3"]->getComponent<Transform>("transform")->setPosition(pos3);
	//mPowerUps["powerup3"]->getComponent<ParticleSystem>("particlesystem")->setEmitting(true);

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

void me::GameManager::powerUpPicked(std::string name)
{
	Vector3 pos = mCircuitoInfo->getRandomPosInside();
	mPowerUps[name]->getComponent<Transform>("transform")->setPosition(pos);
	//mPowerUps[name]->getComponent<ParticleSystem>("particlesystem")->setEmitting(true);
}

void me::GameManager::updatePlayerCheckpoint(std::string playerName, Vector3 pos)
{
	if (playerName == "playerOne")
	{
		mPlayerOneLastCheckpointPos = pos;
	}
	else if (playerName == "playerTwo")
	{
		mPlayerTwoLastCheckpointPos = pos;
	}

}

void me::GameManager::respawnPlayer(std::string playerName)
{
	if (playerName == "playerOne")
	{
		mPlayerOne->getComponent<Transform>("transform")->setPosition(mPlayerOneLastCheckpointPos);
	}
	else if (playerName == "playerTwo")
	{
		mPlayerTwo->getComponent<Transform>("transform")->setPosition(mPlayerTwoLastCheckpointPos);
	}

}



