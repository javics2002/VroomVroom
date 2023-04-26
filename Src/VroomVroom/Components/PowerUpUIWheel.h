#pragma once
#ifndef __VROOMVROOM_POWER_UP_UI_WHEEL
#define __VROOMVROOM_POWER_UP_UI_WHEEL

#include "EntityComponent/Components/Component.h"
#include <string>
#include <list>


namespace me {
	class UISpriteRenderer;
	class Timer;
}

namespace VroomVroom {

	/**
	A component class that represents a power-up wheel that randomly rotates between PowerUps before selecting a definitive one.
	*/
	class PowerUpUIWheel : public me::Component
	{

	public:
		PowerUpUIWheel();
		~PowerUpUIWheel();

		void start() override;
		void update(const double& dt) override;

		/*
		Begins the Spinning effect, ending in the default or last set time, and landing on the last set sprite.
		*/
		void startSpinEffect();

		/*
		Spins the wheel and lands on a set Sprite.
		@param secs Seconds the spin lasts.
		@param materialName Name of the Sprite Material to land on.
		*/
		void spinForSecondsAndLandOnSprite(float secs, std::string materialName);

		/*
		Adds a sprite to the list of sprites shown when spinning the wheel.
		@param materialName Name of the Sprite Material to add to the spinning wheel.
		*/
		void addSpriteNameToPool(std::string materialName);

		void setSpinSpeed(float spinSpeed);
		void setLinked(std::string linkedUISpriteName);


	private:
		// Described in component
		float mSpinSpeed;
		me::UISpriteRenderer* mLinkedUISprite;

		// For internal purposes
		std::list<std::string> mAvailableSpriteNames;	// Dictated by the PowerUp Wheel Manager, which knows of each PowerUp and the name of its Sprite. Calls addSpriteNameToPool to add.
		std::string mSpriteToLandOn;
		std::string mLinkedUISpriteName;
		bool mSpinning;
		me::Timer* mSpriteIntervalTimer;
		me::Timer* mSpinTimer;
		float mTotalSpinTime;	// This comes from the PowerUp Wheel Manager, which calls spinForSeconds

		/*
		Stops the spinning wheel on a set sprite.
		@param materialName Name of the Sprite Material to stop the spinning wheel on.
		*/
		void stopSpinOnSprite(std::string materialName);
	};
}
#endif

