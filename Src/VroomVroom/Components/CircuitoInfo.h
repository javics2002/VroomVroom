#pragma once
#ifndef __VROOMVROOM_CIRCUITOINFO
#define __VROOMVROOM_CIRCUITOINFO

#include "EntityComponent/Components/Component.h"
#include "Utils/Vector3.h"

class CircuitoInfo : public me::Component {
private:
protected:
	me::Vector3 mPosition; //0,0,0

	// multiply by scale
	float mHalfWidthInner; //72 -> 36
	float mHalfWidthOuter; //88 -> 44
	float mHalfHeightInner; //3,4 -> 1,7
	float mHalfHeightOuter; // 16 -> 8
	float mRadiusInner; //1,7
	float mRadiusOuter; //8


public:

	bool isCircuitInside(me::Vector3 pos);
	me::Vector3 getRandomPosInside();
	const float pi = 3.14159f;

};

#endif