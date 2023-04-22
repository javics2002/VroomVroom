#pragma once
#ifndef __VROOMVROOM_CIRCUITOINFO
#define __VROOMVROOM_CIRCUITOINFO

#include "EntityComponent/Components/Component.h"
#include "Utils/Vector3.h"

namespace VroomVroom {
	/**
	Stores information about the circuits area
	*/
	class CircuitInfo : public me::Component {
	protected:
		me::Vector3 mPosition; //0,0,0

		// multiply by scale
		float mHalfWidthInner; //72 -> 36
		float mHalfWidthOuter; //88 -> 44
		float mHalfHeightInner; //3,4 -> 1,7
		float mHalfHeightOuter; // 16 -> 8
		float mRadiusInner; //1,7
		float mRadiusOuter; //8

		int mLaps;

	public:
		CircuitInfo();
		~CircuitInfo();

		const float pi = 3.14159f;
		bool isCircuitInside(me::Vector3 pos);
		me::Vector3 getRandomPosInside();
		void setPosition(me::Vector3 pos);
		void setInfo(float halfWidthInner, float halfWidthOuter,
			float halfHeightInner, float halfHeightOuter, float radiusInner, float radiusOuter);

		void setLaps(int laps);
		int getLaps();
	};
}
#endif