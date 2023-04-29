#pragma once
#ifndef __VROOMVROOM_CIRCUITOINFO
#define __VROOMVROOM_CIRCUITOINFO

#include "EntityComponent/Components/Component.h"
#include "EntityComponent/Components/UISpriteRenderer.h"
#include "Utils/Vector3.h"
#include "Utils/Timer.h"
#include <string>
#include <vector>
#include <map>

namespace VroomVroom {
	class VehicleController;
	class Checkpoint;

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

		bool mRaceStarted = false;
		me::Timer* mTimer = nullptr;

		std::vector<VehicleController*> mVehicles;
		std::map<int, Checkpoint*> mCheckpoints;

		me::UISpriteRenderer* mCountdownSprite;

		void calculatePlaces();

	public:
		CircuitInfo();
		~CircuitInfo();

		void start() override;
		void update(const double& dt) override;

		bool isCircuitInside(me::Vector3 pos);
		me::Vector3 getRandomPosInside();
		void setPosition(me::Vector3 pos);
		void setInfo(float halfWidthInner, float halfWidthOuter,
			float halfHeightInner, float halfHeightOuter, float radiusInner, float radiusOuter);

		void setLaps(int laps);
		int getLaps();

		void setDeathHeight(float deathHeight);
		float getDeathHeight();

		void startRace();
		std::string getFinishTime();

		void addVehicle(VehicleController* newVehicle);
		void addCheckpoint(Checkpoint* newCheckpoint);
	};
}
#endif