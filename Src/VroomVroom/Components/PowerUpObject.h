#pragma once
#ifndef __VROOMVROOM_POWER_UP_OBJECT
#define __VROOMVROOM_POWER_UP_OBJECT


#include "EntityComponent/Components/Component.h"

namespace me {
	class Timer;
	class Transform;
	class AudioSource;
	class Entity;
}

namespace VroomVroom {
	/**
	* Enumeration representing the different types of power-ups that can be picked up by a player.
	*/
	enum PowerUpType
	{
		NERF, OIL, THUNDER
	};

	/**
	A box that gives the player that touches it a random power-up,
	and then disappears for a short time.
	*/
	class PowerUpObject : public me::Component
	{
	public:
		PowerUpObject();
		~PowerUpObject();

		/**
		* Called when the power-up object is spawned in the game to initialize its variables.
		*/
		void start() override;

		/**
		* Checks if the object is picked up to deactivate its mesh or to make it rotate if it is not picked.
		*/
		void update(const double& dt) override;

		/**
		* Resets the power-up object
		*/
		void resetPowerUp();

		/**
		* Sets a specific power-up
		* @param type: the power up type to be set.
		*/
		void setPower(PowerUpType type);

		/**
		* Called when the power-up object collides with another entity.
		* @param other: a pointer to the entity that the power-up object collided with.
		*/
		void onCollisionEnter(me::Entity* other) override;

		/*
		* Return the entity of the picked power up (oil or nerf)
		*/
		me::Entity* createOilEntity();
		me::Entity* createNerfEntity();

	private:
		PowerUpType mPowerUp; // the type of power-up that this object represents
		me::Entity* mPowerUpEntity;
		me::AudioSource* mTakePowerAudio; 

		me::Transform* mTransform;
		me::Timer* mTimer;
		float mReviveTime; // the time it takes for the power-up object to respawn after being picked up
		bool mPicked; // whether the power-up object has been picked up by a player
	};
}
#endif

