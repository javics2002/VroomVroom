 #pragma once
#ifndef __VROOMVROOM_OIL
#define __VROOMVROOM_OIL

#include "PowerUp.h"

namespace me {
	class Entity;
}

class Oil : public PowerUp
{
private:
	int mPlayerFriction; // The friction of the player's vehicle before colliding with the Oil
	int mFriction; // The friction value that the Oil sets when a vehicle collides with it

public:
	Oil();
	~Oil();

	void start() override;
	

	/**
	Sets the friction value that the Oil will apply to vehicles that collide with it
	*/
	void setFriction(float friction);

	// Overrides the PowerUp class functions
	void onCollisionEnter(me::Entity* other) override;
	void onCollisionStay(me::Entity* other) override;
	void onCollisionExit(me::Entity* other) override;
};

#endif

