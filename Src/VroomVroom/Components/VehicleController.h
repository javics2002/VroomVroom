#pragma once
#ifndef __VROOMVROOM_VEHICLECONTROLLER
#define __VROOMVROOM_VEHICLECONTROLLER

#include "EntityComponent/Components/Component.h"
#include "VroomVroom/VroomVroomInput.h"
#include "Utils/Vector3.h"
#include "Utils/Vector2.h"
#include <string>

namespace me {
	class Transform;
	class RigidBody;
}

namespace VroomVroom {
	class Checkpoint;
	class CircuitInfo;

	enum PowerUpType : int;

	/**
	Enables player input for their car.
	*/
	class VehicleController : public me::Component {
	private:
		// predefine constant parameters
		float maxSpeed = 10.0f;
		float maxAngularSpeed = 3.5f;

		float mAcceleration;
		float mDeceleration;
		float mRotationSpeed;
		float mDriftFactor;

		//Index of the last valid checkpoint
		int mCheckpointIndex;
		me::Vector3 mLastCheckpointPosition;

		//Current lap of this vehicle
		int mLap;

		bool mPowerUp;
		PowerUpType mPowerUpType;

		PlayerNumber mPlayerNumber;

		//Current place of the vehicle in the race.
		int mPlace;
		//Stores the final timer when the vehicle reaches the finish line.
		std::string mFinishTime;

		me::Transform* mTransform;
		me::RigidBody* mRigidBody;
		CircuitInfo* mCircuitInfo;

		bool mControllable;

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

		/**
		Limits a value to a max value
		@param Value the value to be limited
		@param Max the maximum value that the value can take
		@returns Value of the fitted value
		*/
		float clampMax(float value, float max);

		/**
		Apply the rotation physics to the car, using angularSpeed.
		@param Dt the time lapsed from previous frame
		@param DeltaX turn direction
		*/
		void applyRotation(const double& dt, float deltaX);
		
		/**
		Apply the rotation physics to the car, using angularSpeed.
		@param Dt the time lapsed from previous frame
		@param DeltaX turn direction
		*/
		void applyPush(const double& dt, bool accelerate, bool decelerate);

	public:
		VehicleController();

		void start() override;
		void update(const double& dt) override;

		// Initializes the speed, rotation speed, and drift factor variables
		void setAccelerationAndRotation(float acceleration, float angularSpeed, float driftFactor);

		void setPowerUp(PowerUpType powerUpType);

		inline void setPlayerNumber(PlayerNumber playerNumber) {
			mPlayerNumber = playerNumber;
		}

		void onCollisionEnter(me::Entity* other) override;
		void onCollisionExit(me::Entity* other) override;
	};
}
#endif