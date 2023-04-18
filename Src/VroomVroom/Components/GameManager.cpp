#include "GameManager.h"

#include "EntityComponent/Entity.h"
#include "EntityComponent/Scene.h"
#include "EntityComponent/SceneManager.h"
#include "EntityComponent/Components/Transform.h"
#include "EntityComponent/Components/ParticleSystem.h"
#include "Input/InputManager.h"

#include "VehicleController.h"
#include "CameraFollow.h"
//#include "CircuitoInfo.h"

using namespace me;

GameManager::GameManager() {

}

GameManager::~GameManager()
{
}

void GameManager::start()
{
	mGameState = GAMESTATE_LOADMAINMENU;
}

void GameManager::update()
{
	switch (mGameState)
	{

	case GameState::GAMESTATE_LOADMAINMENU:
		if (sceneManager().getScene("MainMenu") == nullptr)
		{
			sceneManager().addScene("MainMenu");
		}
		sceneManager().setActiveScene("MainMenu");
		sceneManager().loadEntities("mainmenu.lua");
		mGameState = GameState::GAMESTATE_MAINMENU;
		break;

	case GameState::GAMESTATE_STARTGAME:

		if (sceneManager().getScene("Race") == nullptr)
		{
			sceneManager().addScene("Race");
		}
		sceneManager().removeScene("MainMenu");
		sceneManager().setActiveScene("Race");
		sceneManager().loadEntities("race.lua");
		//setEntitiesInfo();
		//setPowerUps();
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
		break;
	case GameState::GAMESTATE_MAINMENU:
	case GameState::GAMESTATE_GAMEOVER:
		//sceneManager().update();
		processInput();
		break;
	default:
		break;
	}


}



void GameManager::setEntitiesInfo()
{
	//mPlayerOne = sceneManager().getActiveScene()->findEntity("playerOne").get();
	//mPlayerOne->getComponent<VehicleController>("vehiclecontroller")->setInput("LEFT1", "RIGHT1", "JOYSTICK1", "ACELERATE1", "DECELERATE1","DRIFT1", "USE1");
	//mPlayerOneLastCheckpointPos = mPlayerOne->getComponent<Transform>("transform")->getPosition();
	////setupInput(1);
	//if (mNumPlayer == NumPlayer::TwoPlayer)
	//{
	//	mPlayerTwo = sceneManager().getActiveScene()->findEntity("playerTwo").get();
	//	mPlayerTwo->getComponent<VehicleController>("vehiclecontroller")->setInput("LEFT2", "RIGHT2", "JOYSTICK2", "ACELERATE2", "DECELERATE2", "DRIFT2", "USE2");
	//	mPlayerTwoLastCheckpointPos = mPlayerOne->getComponent<Transform>("transform")->getPosition();
	//	//setupInput(2);
	//}

	//mCircuito = sceneManager().getActiveScene()->findEntity("circuito").get();
	//mCircuitoInfo = mCircuito->getComponent<CircuitoInfo>("circuitoinfo");
	//mMeta = sceneManager().getActiveScene()->findEntity("meta").get();

	//mPowerUps["powerup1"] = sceneManager().getActiveScene()->findEntity("powerup1").get();
	//mPowerUps["powerup2"] = sceneManager().getActiveScene()->findEntity("powerup2").get();
	//mPowerUps["powerup3"] = sceneManager().getActiveScene()->findEntity("powerup3").get();
}

/*
void GameManager::setupInput(int player)
{
	Input left, right, joy, acelerate, decelerate, drift, use;
	if (player == 2)
	{
		//"LEFT2", "RIGHT2", "JOYSTICK2", "ACELERATE2", "DECELERATE2", "DRIFT2", "USE2"
		//	<-		  ->						/\			\/						P
		//										A			B					 LB/LT
		//										X			O					 L1/L2
		left.type = INPUTTYPE_KEYBOARD;
		left.which = SDLK_LEFT;
		inputManager().addButton("LEFT2", left);

		right.type = INPUTTYPE_KEYBOARD;
		right.which = SDLK_RIGHT;
		inputManager().addButton("RIGHT2", right);

		joy.type = INPUTTYPE_GAMEPAD_AXIS;
		joy.which = Gamepad_JOY2;
		inputManager().addButton("JOYSTICK2", joy);

		if (mPlayerTwoType == PlayerInputType::Keyboard)
		{
			acelerate.type = INPUTTYPE_KEYBOARD;
			acelerate.which = SDLK_UP;
			inputManager().addButton("ACELERATE2", acelerate);

			decelerate.type = INPUTTYPE_KEYBOARD;
			decelerate.which = SDLK_DOWN;
			inputManager().addButton("DECELERATE2", decelerate);

			drift.type = INPUTTYPE_KEYBOARD;
			drift.which = SDLK_P;
			inputManager().addButton("DRIFT2", drift);

			use.type = INPUTTYPE_KEYBOARD;
			use.which = SDLK_P;
			inputManager().addButton("USE2", use);
		}
		else
		{
			acelerate.type = INPUTTYPE_KEYBOARD;
			acelerate.which = GamepadA;
			inputManager().addButton("ACELERATE2", acelerate);

			decelerate.type = INPUTTYPE_KEYBOARD;
			decelerate.which = GamepadB2;
			inputManager().addButton("DECELERATE2", decelerate);

			drift.type = INPUTTYPE_KEYBOARD;
			drift.which = GamepadLBLT2;
			inputManager().addButton("DRIFT2", drift);

			use.type = INPUTTYPE_KEYBOARD;
			use.which = GamepadStart2;
			inputManager().addButton("USE2", use);

		}
	}
	else if (player == 1)
	{
		//"LEFT1", "RIGHT1", "JOYSTICK1", "ACELERATE1", "DECELERATE1","DRIFT1", "USE1"
		//	 A		   D						W			  S					 SPACE
		//										A			  B					 LB/LT
		//										X			  O					 L1/L2
		left.type = INPUTTYPE_KEYBOARD;
		left.which = SDLK_A;
		inputManager().addButton("LEFT1", left);

		right.type = INPUTTYPE_KEYBOARD;
		right.which = SDLK_D;
		inputManager().addButton("RIGHT1", right);

		joy.type = INPUTTYPE_GAMEPAD_AXIS;
		joy.which = Gamepad_JOY1;
		inputManager().addButton("JOYSTICK1", joy);

		if (mPlayerOneType == PlayerInputType::Keyboard)
		{
			acelerate.type = INPUTTYPE_KEYBOARD;
			acelerate.which = SDLK_W;
			inputManager().addButton("ACELERATE2", acelerate);

			decelerate.type = INPUTTYPE_KEYBOARD;
			decelerate.which = SDLK_S;
			inputManager().addButton("DECELERATE2", decelerate);

			drift.type = INPUTTYPE_KEYBOARD;
			drift.which = SDLK_K;
			inputManager().addButton("DRIFT2", drift);

			use.type = INPUTTYPE_KEYBOARD;
			use.which = SDLK_SPACE;
			inputManager().addButton("USE2", use);
		}
		else
		{
			acelerate.type = INPUTTYPE_KEYBOARD;
			acelerate.which = GamepadA2;
			inputManager().addButton("ACELERATE2", acelerate);

			decelerate.type = INPUTTYPE_KEYBOARD;
			decelerate.which = GamepadB2;
			inputManager().addButton("DECELERATE2", decelerate);

			drift.type = INPUTTYPE_KEYBOARD;
			drift.which = GamepadLBLT2;
			inputManager().addButton("DRIFT2", drift);

			use.type = INPUTTYPE_KEYBOARD;
			use.which = GamepadStart2;
			inputManager().addButton("USE2", use);

		}
	}
}

*/

void GameManager::setPowerUps()
{
	//Seguro que la queremos random? Esos bucles no parecen muy eficaces

	//Vector3 pos1, pos2, pos3;
	//pos1 = mCircuitoInfo->getRandomPosInside();

	////distance should be change, multiply by scale
	//do {
	//	pos2 = mCircuitoInfo->getRandomPosInside();
	//} while ((pos2 - pos1).magnitude() < 2.0f);

	//do {
	//	pos3 = mCircuitoInfo->getRandomPosInside();
	//} while ((pos3 - pos1).magnitude() < 2.0f || (pos3 -pos2).magnitude() < 2.0f);

	//mPowerUps["powerup1"]->getComponent<Transform>("transform")->setPosition(pos1);
	////mPowerUps["powerup1"]->getComponent<ParticleSystem>("particlesystem")->setEmitting(true);
	//mPowerUps["powerup2"]->getComponent<Transform>("transform")->setPosition(pos2);
	////mPowerUps["powerup2"]->getComponent<ParticleSystem>("particlesystem")->setEmitting(true);
	//mPowerUps["powerup3"]->getComponent<Transform>("transform")->setPosition(pos3);
	////mPowerUps["powerup3"]->getComponent<ParticleSystem>("particlesystem")->setEmitting(true);
}



void GameManager::startGame(PlayerNumber num)
{
	mNumPlayer = num;
	mGameState = GameState::GAMESTATE_STARTGAME;
}

void GameManager::mainMenu()
{
	mGameState = GameState::GAMESTATE_LOADMAINMENU;
}

void GameManager::processInput()
{
	std::cout << mGameState << std::endl;

	mGameState = GAMESTATE_STARTGAME;
	std::cout << me::inputManager().getAxis("HORIZONTAL") << mGameState << std::endl;

}

void GameManager::powerUpPicked(std::string name)
{
	//Vector3 pos = mCircuitoInfo->getRandomPosInside();
	//mPowerUps[name]->getComponent<Transform>("transform")->setPosition(pos);
	//mPowerUps[name]->getComponent<ParticleSystem>("particlesystem")->setEmitting(true);
}

void GameManager::updatePlayerCheckpoint(std::string playerName, Vector3 pos)
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

void GameManager::respawnPlayer(std::string playerName)
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



