#pragma once

#ifndef __VROOMVROOM_WHEEL_CONTROLLER
#define __VROOMVROOM_WHEEL_CONTROLLER

#include "EntityComponent/Components/Component.h"
#include "Utils/Vector3.h"
#include <string>

namespace me {
	//Threshold of rotation a wheel cannot surpass.
	const float Y_ROTATION_THRESHOLD = 20.0f;
	//Degrees per step a wheel will spin laterally.
	const float Y_STEP_ROTATION = 0.3f;
	//Rotation factor the speed of the kart will be multiplied by.
	const float Z_ROTATION_FACTOR = 0.5f;

	class WheelController : public Component
	{
	private:
		float mXRotation;
		float mYRotation;
		float mSpeed;
		std::string mLeftButton;
		std::string mRightButton;
		std::string mAccelerateButton;
		std::string mDecelerateRightButton;
		std::string mSpinStick;
	public:
		WheelController();
		~WheelController();

		void update() override;

		//Set input info to vehicle controller
		void setInput(std::string left, std::string right, std::string deltaX,
			std::string acelerate, std::string decelerate);
	};	
}
#endif	