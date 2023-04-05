#pragma once

#ifndef __VROOMVROOM_WHEEL_CONTROLLER
#define __VROOMVROOM_WHEEL_CONTROLLER

#include "EntityComponent/Components/Component.h"
#include <string>

/**
Manages wheel behaviour to correspond with the actions
of the vehicle, so they rotate and turn according to it.
*/
class WheelController : public me::Component
{
	//Threshold of rotation a wheel cannot surpass.
	const float Y_ROTATION_THRESHOLD = 20.0f;
	//Degrees per step a wheel will spin laterally.
	const float Y_STEP_ROTATION = 0.3f;
	//Rotation factor the speed of the kart will be multiplied by.
	const float Z_ROTATION_FACTOR = 0.5f;

	float mXRotation;
	float mYRotation;
	float mSpeed;
public:
	WheelController();
	~WheelController();

	void update() override;
};
#endif	