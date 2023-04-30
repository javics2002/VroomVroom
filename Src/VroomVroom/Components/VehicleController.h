#pragma once
#ifndef __VROOMVROOM_VEHICLECONTROLLER
#define __VROOMVROOM_VEHICLECONTROLLER

#include "EntityComponent/Components/Component.h"
#include "EntityComponent/Components/UIText.h"
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

	class VehicleController : public me::Component {
	private:
		/*
		* Parameters for the vehicleController.
		*/
		float mMaxSpeed;
		float mMaxAngularSpeed;

		float mAcceleration;
		float mRotationSpeed;
		float mDriftFactor;

		float mLinearDamping; 
		float mAngularDamping;

		float mAccelerationBoost;
		float mSteeringBoost;
		float mSpeedBasedRotationMultiplier;
		
		/*
		* Information about the checkpoints and lap counter
		*/
		int mCheckpointIndex; //Index of the last valid checkpoint
		me::Vector3 mLastCheckpointPosition;
		int mLap; //Current lap of this vehicle
		int mPlace; //Current place of the vehicle in the race.

		bool mPowerUp;
		PowerUpType mPowerUpType;
		PlayerNumber mPlayerNumber;


		std::string mFinishTime; // Stores the final timer when the vehicle reaches the finish line.


		/*
		* Information about entity's components
		*/
		me::Transform* mTransform;
		me::RigidBody* mRigidBody;
		CircuitInfo* mCircuitInfo;
		PowerUpUIWheel* mPowerUpUIWheel;
		me::UIText* mLapsText;

		bool mControllable;

		/*
		Checks if buttonName has been pressed for this playerNumber
		by calling inputManager().getButton(buttonName + mPlayerNumber).
		@returns Whether this player has pressed buttonName.
		*/
		bool getPlayerButton(std::string buttonName);

		/*
		Checks axisName value by calling inputManager().getButton(axisName + mPlayerNumber).
		@returns Value of axisName of this player
		*/
		float getPlayerAxis(std::string axisName);

		/*
		Takes a float reference "value" and two float parameters "min" and "max". 
		Its purpose is to limit the value of "value" to be within the range specified by "min" and "max".
		If "value" is smaller than "min", "value" is set to "min". If "value" is larger than "max", "value" is set to "max".
		If "value" is already within the range, it is left unchanged.
		@param Value the value to be limited
		@param Max: the maximum value that the "value" can take
		@param Min: the minimum value that the "value" can take
		*/
		void clamp(float& value, float min, float max);

		/*
		Returns a boolean value that indicates whether an object is currently moving backwards or not.
		It does this by checking the object's current velocity or direction vector and determining whether it is pointing in the opposite direction of its forward vector.
		If the velocity vector points in the opposite direction of the forward vector, then the object is considered to be moving backwards, and the method returns "true". 
		Otherwise, if the velocity vector is pointing in the same direction as the forward vector or if the object is stationary, the method returns "false".

		@returns Whether the vehicle is going backwards or not
		*/ 
		bool isMovingBackwards();

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

		void setAccelerationAndRotation(float acceleration, float angularSpeed, float driftFactor);
		void setMaxSpeedAndRotationSpeed(float maxSpeed, float maxRotationSpeed);
		void setLinearAndAngularDamping(float linearDrag, float angularDrag);
		void setAccelerationAndSteeringBoost(float accelerationBoost, float steeringBoost);
		void setSpeedBasedRotationMultiplier(float speedBasedFactor);

		void setPlayerNumber(PlayerNumber playerNumber);
		void setControllable(bool controllable);
		void setPowerUp(PowerUpType powerUpType);
		void setPowerUpUI();

		PlayerNumber getPlayerNumber();

		void setPlace(int newPlace);
		int getPlace();
		int getLap();
		int getChekpointIndex();


		/*
		Its purpose is to handle collision events that occur when the entity collides with another entity in the game world.
		@param other The method takes a pointer to the other entity involved in the collision as a parameter.
		*/
		void onCollisionEnter(me::Entity* other) override;
	};
}
#endif