#pragma once
#ifndef __VROOMVROOM_GAMEMANAGER
#define __VROOMVROOM_GAMEMANAGER

#include "EntityComponent/Components/Component.h"
#include "Utils/Singleton.h"
#include "Utils/Vector3.h"
#include <string>
#include <unordered_map>

enum class GameState {
	LoadMainMenu,
	MainMenu,
	StartGame,
	InGame,
	LoadGameOver,
	GameOver
};
enum class NumPlayer {
	OnePlayer,
	TwoPlayer
};

enum class PlayerInputType {
	Keyboard,
	Gamepad
};

namespace me {
	class Entity;
}

class CircuitoInfo;


class GameManager : public me::Component, public me::Singleton<GameManager>
{
	friend Singleton<GameManager>;

	GameManager();

protected:
	me::Entity* mCircuito = nullptr;
	CircuitoInfo* mCircuitoInfo = nullptr;
	me::Entity* mPlayerOne = nullptr;
	me::Entity* mPlayerTwo = nullptr;
	PlayerInputType mPlayerOneType = PlayerInputType::Keyboard;
	PlayerInputType mPlayerTwoType = PlayerInputType::Keyboard;
	me::Vector3 mPlayerOneLastCheckpointPos;
	me::Vector3 mPlayerTwoLastCheckpointPos;
	me::Entity* mMeta = nullptr;
	std::unordered_map<std::string, me::Entity*> mPowerUps;
	GameState mGameState = GameState::LoadMainMenu;
	NumPlayer mNumPlayer = NumPlayer::OnePlayer;

	void setEntitiesInfo();
	void setPowerUps();

	//void setupInput(int player);


public:
	GameManager& operator=(const GameManager& o) = delete;
	GameManager(const GameManager& o) = delete;
	~GameManager() override;


	void start() override;
	void update() override;
	void startGame(NumPlayer num);
	void mainMenu();

	void powerUpPicked(std::string name);

	void updatePlayerCheckpoint(std::string playerName, me::Vector3 pos);

	void respawnPlayer(std::string playerName);
};


/**
This macro defines a compact way for using the singleton GameManager, instead of
writing GameManager::instance()->method() we write gameManager().method()
*/
inline GameManager& gameManager() {
	return *GameManager::instance();
}
#endif