#pragma once
#ifndef __VROOMVROOM_POWER_UP
#define __VROOMVROOM_POWER_UP

#include "EntityComponent/Components/Component.h"

namespace VroomVroom {
	/**
	A component class that represents a power-up in the game.
	*/
	class PowerUp : public me::Component
	{
	public:
		PowerUp();
		~PowerUp();
	};
}
#endif

