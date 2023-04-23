#pragma once
#ifndef __VROOMVROOM_CIRCUITOINFO
#define __VROOMVROOM_CIRCUITOINFO

#include "EntityComponent/Components/Component.h"
#include "Utils/Vector3.h"
#include "Utils/Timer.h"
#include <string>

namespace VroomVroom {
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

		me::Timer* mTimer = nullptr;

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
	};
}
#endif