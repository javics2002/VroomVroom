#pragma once
#ifndef __VROOMVROOM_VEHICLECONTROLLER
#define __VROOMVROOM_VEHICLECONTROLLER

#include "EntityComponent/Components/Component.h"
#include "VroomVroom/VroomVroomInput.h"
#include <string>

enum PowerUpType : int;

/**
Enables player input for their car.
*/
class VehicleController : public me::Component {
private:
	float mSpeed;
	float mRotationSpeed;
	float mDriftFactor;

	//Index of the last valid checkpoint
	int mCheckpointIndex;

	bool mPowerUp;
	PowerUpType mPowerUpType;

	PlayerNumber mPlayerNumber;

	/**
	Checks if buttonName has been pressed for this playerNumber
	by calling inputManager().getButton(buttonName + mPlayerNumber).
	@returns Whether this player has pressed buttonName.
	*/
	bool getPlayerButton(std::string buttonName);

	/**
	Checks axisName value by calling inputManager().getButton(axisName + mPlayerNumber).
	@returns Value of axisName of this player
	*/
	float getPlayerAxis(std::string axisName);

public:
	VehicleController();

	void start() override;
	void update() override;

	// Initializes the speed, rotation speed, and drift factor variables
	void setSpeedAndDrift(float speed, float angularSpeed, float driftFactor);

	void setPowerUp(PowerUpType powerUpType);

	inline void setPlayerNumber(PlayerNumber playerNumber) {
		mPlayerNumber = playerNumber;
	}

	/**
	Get the speed value of the Vehicle Controller component.
	@return A float object representing the speed.
	*/
	float getSpeed();

	//void onCollisionEnter(Entity other) override {
	//    if (other.hascomponent<Checkpoint>("Checkpoint")) {
	//        if (checkpoint.index == checkpointIndex + 1)
	//            checkpointIndex++; 
	//        else if (checkpoint.index == checkpointIndex - 1)
	//            checkpointIndex--; //Vas marcha atras por alguna razon
	//    }
	//}

	//void onCollisionExit(Entity other) override {
	//    if (other.hascomponent<Checkpoint>("Checkpoint")) {
	//        if (checkpoint.index == checkpointIndex + 1)
	//            checkpointIndex++;
	//        else if (checkpoint.index == checkpointIndex)
	//            checkpointIndex--; //Vas marcha atras por alguna razon
	//    }
	//}
};
#endif