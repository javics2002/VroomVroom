#pragma once
#ifndef __VROOMVROOM_CIRCUITOINFO
#define __VROOMVROOM_CIRCUITOINFO

#include "EntityComponent/Component.h"
#include "EntityComponent/FactoryComponent.h"
#include "Utils/Vector3.h"

#include <string>
#include <vector>
#include <map>

namespace me {
	class Timer;
	class UISpriteRenderer;
}

namespace VroomVroom {
	class VehicleController;
	class Checkpoint;


	class FactoryCirtuitInfo : public me::FactoryComponent {
	public:
		me::Component* create(me::Parameters& params) override;
		void destroy(me::Component* component) override;
	};

	/**
	Stores information about the circuits area
	*/
	class CircuitInfo : public me::Component {
	protected:
		me::Vector3 mPosition; //0,0,0

		//If a vehicle falls beneath this height, it will respawn.
		float mDeathHeight;

		// multiply by scale
		float mHalfWidthInner; //72 -> 36
		float mHalfWidthOuter; //88 -> 44
		float mHalfHeightInner; //3,4 -> 1,7
		float mHalfHeightOuter; // 16 -> 8
		float mRadiusInner; //1,7
		float mRadiusOuter; //8

		int mLaps;

		bool mTimeIsFrozen = false;
		float mFreezeSecondsLeft;

		bool mRaceStarted = false;
		bool mRaceFinished = false;
		int mCarsFinished = 0;
		me::Timer* mTimer = nullptr;
		me::Timer* mFinishTimer = nullptr;
		me::Timer* mFreezeTimer = nullptr;

		std::vector<VehicleController*> mVehicles;
		std::map<int, Checkpoint*> mCheckpoints;

		me::UISpriteRenderer* mCountdownSprite;

		void calculatePlaces();

	public:
		CircuitInfo();
		~CircuitInfo();

		void start() override;
		void update(const double& dt) override;

		/**
		* Determines if a given position is inside the circuit's area.
		* @param pos A Vector3 representing the position to check.
		* @return True if the position is inside the circuit, false otherwise.
		*/
		bool isCircuitInside(me::Vector3 pos);
		/**
		* Generates a random position inside the circuit's area.
		* @return A Vector3 representing a random position inside the circuit.
		*/
		me::Vector3 getRandomPosInside();
		/**
		 * Set the position of the circuit in the game world.
		 * @param pos A Vector3 representing the new position.
		 */
		void setPosition(me::Vector3 pos);
		/**
		 * Set the parameters for the circuit's shape.
		 * @param halfWidthInner The half-width of the inner part of the circuit.
		 * @param halfWidthOuter The half-width of the outer part of the circuit.
		 * @param halfHeightInner The half-height of the inner part of the circuit.
		 * @param halfHeightOuter The half-height of the outer part of the circuit.
		 * @param radiusInner The radius of the inner part of the circuit.
		 * @param radiusOuter The radius of the outer part of the circuit.
		 */
		void setInfo(float halfWidthInner, float halfWidthOuter,
			float halfHeightInner, float halfHeightOuter, float radiusInner, float radiusOuter);
		/**
		 * Set the number of laps for the race.
		 * @param laps The number of laps.
		 */
		void setLaps(int laps);
		/**
		 * Get the number of laps for the race.
		 * @return The number of laps.
		 */
		int getLaps();

		/**
		 * Get the number of cars that have finished the race.
		 * @return The number of cars that have finished the race.
		 */
		int getCarFinished();
		/**
		 * Set the height at which a car will respawn if it falls off the circuit.
		 * @param deathHeight The height at which a car will respawn.
		 */
		void setDeathHeight(float deathHeight);
		/**
		 * Get the height at which a car will respawn if it falls off the circuit.
		 * @return The height at which a car will respawn.
		 */
		float getDeathHeight();

		/**
		* Start the race timer
		*/
		void startRace();
		/**
		* Get the elapsed time since the race started.
		* @return The elapsed time as a string in the format "HH:MM:SS".
		*/
		std::string getElapsedTime();

		/**
		* Freeze the Race timer for a certain time.
		* @param secs Number of seconds to freeze the timer for.
		*/
		void freezeTimer(float secs);

		/**
		* Get the finish time of the race.
		* @return The finish time as a string in the format "HH:MM:SS".
		*/
		std::string getFinishTime();

		/**
		* Add a new vehicle to the race.
		* @param newVehicle A pointer to the VehicleController object representing the new vehicle to be added.
		*/
		void addVehicle(VehicleController* newVehicle);

		/**
		* Add a new checkpoint to the race.
		* @param newCheckpoint A pointer to the Checkpoint object representing the new checkpoint to be added.
		*/
		void addCheckpoint(Checkpoint* newCheckpoint);
	};
}
#endif