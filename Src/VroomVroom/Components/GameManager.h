#pragma once
#ifndef __VROOMVROOM_GAMEMANAGER
#define __VROOMVROOM_GAMEMANAGER

#include "EntityComponent/Components/Component.h"
#include "Utils/Singleton.h"
#include "Utils/Vector3.h"
#include <unordered_map>

namespace me {
	
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

	class Entity;


	class GameManager : public Component ,public Singleton<GameManager>
	{
		friend Singleton<GameManager>;
	private:
	protected:
		Entity* mCircuito = nullptr;
		Entity* mPlayerOne = nullptr;
		Entity* mPlayerTwo = nullptr;
		Entity* mMeta = nullptr;
		std::unordered_map<std::string, Entity*> mCheckpoints;
		std::unordered_map<std::string, Entity*> mPowerUps;
		GameState mGameState;
		NumPlayer mNumPlayer;

		void createPowerUps();
		
	public:
		GameManager& operator=(const GameManager& o) = delete;
		GameManager(const GameManager& o) = delete;
		~GameManager() override;

		void start();
		void setEntitiesInfo();
		void update();
		void startGame(NumPlayer num);
		void mainMenu();


	};

	/**
	This macro defines a compact way for using the singleton GameManager, instead of
	writing GameManager::instance()->method() we write gameManager().method()
	*/
	inline GameManager& gameManager() {
		return *GameManager::instance();
	}
}
#endif