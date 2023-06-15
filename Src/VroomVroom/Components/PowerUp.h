#pragma once
#ifndef __VROOMVROOM_POWER_UP
#define __VROOMVROOM_POWER_UP

#include "EntityComponent/Component.h"
#include "EntityComponent/FactoryComponent.h"

namespace VroomVroom {
	/**
	A component class that represents a power-up in the game.
	*/
	class PowerUp : public me::Component
	{
	public:
		PowerUp();
		~PowerUp();

		//Method to be called whenever a player uses a power up, other being the user.
		virtual void use(me::Entity* other);
	};
}
#endif

