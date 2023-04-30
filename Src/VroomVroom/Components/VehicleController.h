#pragma once
#ifndef __VROOMVROOM_VEHICLECONTROLLER
#define __VROOMVROOM_VEHICLECONTROLLER

#include "EntityComponent/Components/Component.h"
#include "VroomVroom/VroomVroomInput.h"
#include "Utils/Vector3.h"
#include <string>

namespace me {
	class Transform;
	class RigidBody;
}

namespace VroomVroom {
	class Checkpoint;
	class CircuitInfo;
	class PowerUpUIWheel;

	enum PowerUpType : int;

	/*
	Enables player input for their car.
	*/
	class VehicleController : public me::Component {
	private:
		float mMaxSpeed;
		float mMaxAngularSpeed;

		float mAcceleration;
		float mDeceleration;
		float mRotationSpeed;
		float mDriftFactor;

		float mLinearDamping; 
		float mAngularDamping;

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
		PowerUpUIWheel* mPowerUpUIWheel;

		bool mControllable;

		/*
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
		Limits a value to a max value or a min value
		@param Value the value to be limited
		@param Max the maximum value that the value can take
		*/
		void clamp(float& value, float min, float max);

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
		void setMaxSpeedAndRotationSpeed(float maxSpeed, float maxRotationSpeed);
		void setLinearAndAngularDamping(float linearDrag, float angularDrag);

		void setPlayerNumber(PlayerNumber playerNumber) {
			mPlayerNumber = playerNumber;
		}

		void setControllable(bool controllable) {
			mControllable = controllable;
		}

		void setPowerUp(PowerUpType powerUpType);
		void setPowerUpUI();

		PlayerNumber getPlayerNumber() {
			return mPlayerNumber;
		}

		void setPlace(int newPlace);
		int getPlace();
		int getLap();
		int getChekpointIndex();

		void onCollisionEnter(me::Entity* other) override;
	};
}
#endif