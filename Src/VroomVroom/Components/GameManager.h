#pragma once
#ifndef __VROOMVROOM_GAMEMANAGER
#define __VROOMVROOM_GAMEMANAGER

#include "EntityComponent/Components/Component.h"
#include "VroomVroom/VroomVroomInput.h"
#include "Utils/Singleton.h"
#include "Utils/Vector3.h"
#include <string>
#include <unordered_map>

enum GameState {
	GAMESTATE_LOADMAINMENU,
	GAMESTATE_MAINMENU,
	GAMESTATE_STARTGAME,
	GAMESTATE_INGAME,
	GAMESTATE_LOADGAMEOVER,
	GAMESTATE_GAMEOVER
};

class Entity;
class CircuitoInfo;

/**
Class GameManager, componente that is singleton, use for control the gamestate
Call sceneManager to load the corrsponding map (.lua file) according to current gameState
*/
class GameManager : public me::Component, public me::Singleton<GameManager>
{
	friend Singleton<GameManager>;

	GameManager();

protected:
	me::Entity* mCircuito = nullptr;
	CircuitoInfo* mCircuitoInfo = nullptr;
	me::Entity* mPlayerOne = nullptr;
	me::Entity* mPlayerTwo = nullptr;
	PlayerInputType mPlayerOneType = PLAYERINPUTTYPE_KEYBOARD;
	PlayerInputType mPlayerTwoType = PLAYERINPUTTYPE_KEYBOARD;
	me::Vector3 mPlayerOneLastCheckpointPos;
	me::Vector3 mPlayerTwoLastCheckpointPos;
	me::Entity* mMeta = nullptr;
	std::unordered_map<std::string, me::Entity*> mPowerUps;
	GameState mGameState = GAMESTATE_LOADMAINMENU;
	PlayerNumber mNumPlayer = PLAYERNUMBER_1;

	//Get reference to all necesary entities from SceneManager
	void setEntitiesInfo();
	//Change powerUps position to some random pos on space of circuit
	void setPowerUps();
	/**
	Assign inputs keys to inputmanager
	@params player: indicate which player we assign (1 || 2)
	*/
	//void setupInput(int player);


public:
	GameManager& operator=(const GameManager& o) = delete;
	GameManager(const GameManager& o) = delete;
	~GameManager() override;

	//Set mGameState to first gameState
	void start() override;

	//Call sceneManger loading map or update entities
	void update() override;

	/**
	Function that change gamestate to startGame when clicked race button in MainMenu
	@param num: indicate the number of player that selected in MainMenu
	*/
	void startGame(PlayerNumber num);

	//Function that change gamestate to loadMainMenu when go back to MainMenu (example: OverMenu to MainMenu)
	void mainMenu();

	/**
	Function that change position to powerup picked to new random pos (powerup is the cube incognit to collision enter, the real powerup is assigned when collisioned, so , use again the powerup incognit)
	@param name : indicate the name of powerup's entity, and searching in unordered map of 3 powerup.
	*/
	void powerUpPicked(std::string name);

	/**
	Save last checkpoint colisioned for which player
	@params playerName: indicate the name of player's entity
	@params pos: indicate the position of checkpoint
	*/
	void updatePlayerCheckpoint(std::string playerName, me::Vector3 pos);

	/**
	If player fall down , respawn which player on the last saved checkpoint position
	@params playerName: indicate the name of player's entity
	*/
	void respawnPlayer(std::string playerName);
};


/**
This macro defines a compact way for using the singleton GameManager, instead of
writing GameManager::instance()->method() we write gameManager()->method()
*/
inline GameManager* gameManager() {
	return GameManager::instance();
}
#endif