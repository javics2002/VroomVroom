#pragma once
#ifndef __VROOMVROOM_VROOMVROOMINPUT
#define __VROOMVROOM_VROOMVROOMINPUT

#include <string>

namespace VroomVroom {
	//Number of the player
	enum PlayerNumber {
		PLAYERNUMBER_1,
		PLAYERNUMBER_2,
		PLAYERNUMBER_MAX //Maximum number of players, don't use it for players!
	};

	//Type of input a player is using to play
	enum PlayerInputType {
		PLAYERINPUTTYPE_KEYBOARD,
		PLAYERINPUTTYPE_GAMEPAD
	};

	/**
	Returns the name of the button for a specific player
	by joining buttonName and playerNumber
	@param buttonName Name of the button.
	@param playerNumber	Number of the player
	@returns Name of the button for the specific player
	*/
	std::string playerButtonName(std::string buttonName, int playerNumber);
}
#endif