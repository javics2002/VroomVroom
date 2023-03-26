#pragma once
#ifndef __VROOMVROOM_CIRCUITOINFO
#define __VROOMVROOM_CIRCUITOINFO

#include "EntityComponent/Components/Component.h"
#include "Utils/Vector3.h"

namespace me {
	class CircuitoInfo : public Component {
	private:
	protected:
		Vector3 mPosition; //0,0,0

		// multiply by scale
		float mHalfWidthInner; //72 -> 36
		float mHalfWidthOuter; //88 -> 44
		float mHalfHeightInner; //3,4 -> 1,7
		float mHalfHeightOuter; // 16 -> 8
		float mRadiusInner; //1,7
		float mRadiusOuter; //8


	public:


		const float pi = 3.14159f;
		bool isCircuitInside(Vector3 pos);
		Vector3 getRandomPosInside();
		void setPosition(Vector3 pos);
		void setInfo(float halfWidthInner, float halfWidthOuter,
			float halfHeightInner, float halfHeightOuter, float radiusInner, float radiusOuter);



	};
}

#endif