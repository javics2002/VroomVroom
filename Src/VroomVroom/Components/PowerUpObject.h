#pragma once
#ifndef __VROOMVROOM_POWER_UP_OBJECT
#define __VROOMVROOM_POWER_UP_OBJECT

#include "EntityComponent/Entity.h"
#include "EntityComponent/Components/Component.h"



/**
* Enumeration representing the different types of power-ups that can be picked up by a player.
*/
enum PowerUpType
{
	NERF, OIL, THUNDER
};


/**
* A component class that represents a power-up object in the game.
*/
class PowerUpObject : public me::Component
{
public:
	PowerUpObject();
	~PowerUpObject();


	/**
	* Called when the power-up object is spawned in the game.
	*/
	void start() override;

	void update() override;

	/**
	* Resets the power-up object
	*/
	void resetPowerUp();

	/**
	* Called when the power-up object collides with another entity.
	* @param other: a pointer to the entity that the power-up object collided with.
	*/
	void onCollisionEnter(me::Entity* other) override;

private:
	PowerUpType mPowerUp; // the type of power-up that this object represents

	float mTime; // the time that has elapsed since the power-up object was picked
	float mReviveTime; // the time it takes for the power-up object to respawn after being picked up
	bool mPicked; // whether the power-up object has been picked up by a player
};


#endif

