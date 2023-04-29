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
		// Variables de estado del coche
		me::Vector2 mSpeed = me::Vector2();
		float mVelocity = 0;
		float mDirection = 0;
		me::Vector2 mPosition = me::Vector2();

		// Variables de física del coche
		//float mAcceleration = 0;
		float mFriction = 0;
		float mGravity = 0;
		float mRotation = 0;

		// flags de movimiento
		bool mDrift = false;
		me::Vector3 vRadius = me::Vector3();
		

		// predefine constant parameters
		float mAcceleration = .0f;
		float mDeceleration = .0f;
		float maxSpeed = 45.5f;
		float minSpeed = 8.5f;
		float minSpeedFraction = 0.2f;
		float maxAngularSpeed = 3.5f;
		float maxRadius = 20.0f;
		float maxCurveAngle = 45.0f;

		//float mSpeed;
		float mRotationFactor;
		float mDriftFactor;
		float lateralForceFactor = 100.0f;

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

		void fixedUpdate();
		void angularSpeed(float deltaX);

		/**
		Limits a value in a specific range.
		@param Value the value to be limited
		@param Min the minimum value that the value can take
		@param Max the maximum value that the value can take
		@returns Value of the fitted value
		*/
		float clamp(float value, float min, float max);

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

#ifdef _DEBUG
		me::Entity* mCompass = nullptr;
		me::Entity* mTurningPoint = nullptr;
		float mCompassDistance = -15.0f;
		void updateCompass(me::Vector3 vForward, float deltaX);
		void updateTurningPoint(float deltaX);
#endif

	public:
		VehicleController();

		void start() override;
		void update(const double& dt) override;

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

		void onCollisionEnter(me::Entity* other) override;
		void onCollisionExit(me::Entity* other) override;
	};
}
#endif