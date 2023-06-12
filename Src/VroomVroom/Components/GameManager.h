#pragma once
#ifndef __VROOMVROOM_GAMEMANAGER
#define __VROOMVROOM_GAMEMANAGER

#include "EntityComponent/Component.h"
#include "VroomVroom/VroomVroomInput.h"
#include "Utils/Singleton.h"

#include <string>
#include <unordered_map>

namespace me {
	class Entity;
}

namespace VroomVroom {
	enum GameState {
		GAMESTATE_MAINMENU,
		GAMESTATE_INGAME,
		GAMESTATE_RESULTS,
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

		GameState mGameState = GAMESTATE_MAINMENU;
		int mNumPlayer = 1;
		PlayerInputType mPlayerOneType = PLAYERINPUTTYPE_KEYBOARD;
		PlayerInputType mPlayerTwoType = PLAYERINPUTTYPE_KEYBOARD;

		int mWinner;

		std::string mWinnerTime;
		std::string mLoserTime;


		int mContPowerUps;

	public:
		GameManager& operator=(const GameManager& o) = delete;
		GameManager();
		GameManager(const GameManager& o) = delete;
		~GameManager() override;

		static GameManager* Instance();

		void start() override;

		//Call sceneManger loading map or update entities
		void update(const double& dt) override;
		/**
		  * Changes the game state.
		  * @param newScene - name of the new game state.
		  */
		void changeState(std::string newScene);
		/**
		 * Gets the number of power-ups collected.
		 * @return - the number of power-ups collected.
		 */
		int getContPowerUps();
		/**
		 * Adds a power-up to the count.
		 */
		void addPowerUp();
		/**
		 * Gets the number of players.
		 * @return - the number of players.
		 */
		int getNumPlayer();
		/**
		 * Sets the time for the winner and their position.
		 * @param winnerTime - the time for the winner.
		 * @param winner - the position of the winner.
		 */
		void setWinnerTime(std::string winnerTime, int winner);
		/**
		 * Sets the time for the loser.
		 * @param loserTime - the time for the loser.
		 */
		void setLoserTime(std::string loserTime);

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