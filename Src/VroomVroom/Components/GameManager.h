#pragma once
#ifndef __VROOMVROOM_GAMEMANAGER
#define __VROOMVROOM_GAMEMANAGER

#include "EntityComponent/Components/Component.h"
#include "VroomVroom/VroomVroomInput.h"
#include "Utils/Singleton.h"
#include "Utils/Vector3.h"
#include <string>
#include <unordered_map>

namespace me {
	class Entity;
}

namespace VroomVroom {
	enum GameState {
		GAMESTATE_LOADMAINMENU,
		GAMESTATE_MAINMENU,
		GAMESTATE_STARTGAME,
		GAMESTATE_INGAME,
		GAMESTATE_LOADGAMEOVER,
		GAMESTATE_GAMEOVER
	};

	/**
	Class GameManager, component that is singleton, use for control the gamestate
	Call sceneManager to load the corrsponding map (.lua file) according to current gameState
	*/
	class GameManager : public me::Component
	{
	protected:
		static GameManager* MInstance;

		GameState mGameState = GAMESTATE_LOADMAINMENU;
		PlayerInputType mPlayerOneType = PLAYERINPUTTYPE_KEYBOARD;
		PlayerInputType mPlayerTwoType = PLAYERINPUTTYPE_KEYBOARD;

	public:
		GameManager& operator=(const GameManager& o) = delete;
		GameManager();
		GameManager(const GameManager& o) = delete;
		~GameManager() override;

		static GameManager* Instance();

		void start() override;

		//Call sceneManger loading map or update entities
		void update(const double& dt) override;
	};


	/**
	This macro defines a compact way for using the singleton GameManager, instead of
	writing GameManager::instance()->method() we write gameManager()->method()
	*/
	inline GameManager* gameManager() {
		return GameManager::Instance();
	}
}
#endif