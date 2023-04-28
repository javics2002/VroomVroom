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
		me::Vector3 mLastCheckpointPosition;

		//Current lap of this vehicle
		int mLap;

		PowerUpType mPowerUpType;

		PlayerNumber mPlayerNumber;

		//Current place of the vehicle in the race.
		int mPlace;
		//Stores the final timer when the vehicle reaches the finish line.
		std::string mFinishTime;

		me::Transform* mTransform = nullptr;
		me::RigidBody* mRigidBody = nullptr;
		CircuitInfo* mCircuitInfo = nullptr;
		PowerUpUIWheel* mPowerUpUIWheel = nullptr;

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

	public:
		VehicleController();

		void start() override;
		void update(const double& dt) override;

		// Initializes the speed, rotation speed, and drift factor variables
		void setSpeedAndDrift(float speed, float angularSpeed, float driftFactor);

		void setPowerUp(PowerUpType powerUpType);

		void setPowerUpUI();

		inline void setPlayerNumber(PlayerNumber playerNumber) {
			mPlayerNumber = playerNumber;
		}
		inline PlayerNumber getPlayerNumber() {
			return mPlayerNumber;
		}

		inline void setControllable(bool controllable) {
			mControllable = controllable;
		}

		/**
		Get the speed value of the Vehicle Controller component.
		@return A float object representing the speed.
		*/
		float getSpeed();

		void setPlace(int newPlace);
		int getPlace();

		int getLap();
		int getChekpointIndex();

		void onCollisionEnter(me::Entity* other) override;
		void onCollisionExit(me::Entity* other) override;
	};
}
#endif