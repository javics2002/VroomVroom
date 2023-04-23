#include "CircuitInfo.h"
#include <cstdlib> //  rand() y srand()
#include <ctime> //  time()
#define _USE_MATH_DEFINES
#include <math.h>

using namespace me;
using namespace VroomVroom;

CircuitInfo::CircuitInfo()
{
	mHalfWidthInner = 0;
	mHalfWidthOuter = 0;
	mHalfHeightInner = 0;
	mHalfHeightOuter = 0;
	mRadiusInner = 0;
	mRadiusOuter = 0;
}

CircuitInfo::~CircuitInfo()
{
}

void CircuitInfo::start()
{
	mTimer = new Timer(false);
}

void CircuitInfo::update(const double& dt)
{
	mTimer->update(dt);
}

bool CircuitInfo::isCircuitInside(Vector3 pos)
{
	// pos.z must be inside (8 , 1.7) || (-1.7 , -8)  vertical
	// Case (-1.7 , 1.7) if pos.x be inside (-36 , 36)

	if( pos.z > mPosition.z + mHalfHeightOuter || 
		pos.z < mPosition.z - mHalfHeightOuter || 
		(pos.z > mPosition.z - mHalfHeightInner && pos.z < mPosition.z +mHalfHeightInner
		&& pos.x > mPosition.x - mHalfWidthInner && pos.x < mPosition.x + mHalfHeightInner ) )
		return false;

	//pos.x must be inside (-44 , 44) horizontal
	if (pos.x > mPosition.x + mHalfWidthOuter ||
		pos.x < mPosition.x - mHalfWidthOuter)
		return false;

	/*
	|---------------------------|
	|	|-------------------|	|
	|	|-------------------|	|
	|---------------------------|
	*/
	Vector3 pointLeft = Vector3(mPosition.x -mHalfWidthInner , mPosition.y , mPosition.z);
	Vector3 pointRight = Vector3(mPosition.x + mHalfWidthInner, mPosition.y , mPosition.z);
	
	Vector3 dist;
	float distance;
	// if pos.x is in (36 , 44)
	if (pos.x > mPosition.x + mHalfWidthInner ) {
		dist = pos - pointRight;
		distance = dist.magnitude();
		if (distance < mRadiusInner || distance > mRadiusOuter)
			return false;
	}

	// if pos.x is in (-44, -36),
	if (pos.x < mPosition.x - mHalfHeightInner) {
		dist = pos - pointLeft;
		distance = dist.magnitude();
		if (distance < mRadiusInner || distance > mRadiusOuter)
			return false;
	}

	return true;
}

Vector3 CircuitInfo::getRandomPosInside()
{
	float x, z , radius;
	std::srand(std::time(nullptr));

	//range (-44 ,44)
	x = -mHalfWidthOuter + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / (mHalfWidthOuter*2));
	
	//range (-36 , 36)
	if (x < mHalfWidthInner || x > -mHalfWidthInner) {
		bool is_negative = rand() % 2 == 0;

		z= static_cast<float>(rand()) / static_cast<float>(RAND_MAX / (mHalfHeightOuter - mHalfHeightInner));

		if (is_negative)
			z = -z - mHalfHeightInner;
		else
			z = z + mHalfHeightInner;

		x += mPosition.x;
		z += mPosition.y;
	}
	else {
		radius = mRadiusInner + static_cast<float>(RAND_MAX / (mRadiusOuter - mRadiusInner));
		float angle = rand() % 360;
		float radians = angle * M_PI / 180.0f;
		
		x = radius * std::cos(radians);
		if (x > 0)
			x = mPosition.x + mHalfWidthInner- + x;
		else
			x = mPosition.x - mHalfWidthInner - x;
		z = radius * std::sin(radians) + mPosition.z;
	}
	
	return Vector3(x,mPosition.y,z);
}

void CircuitInfo::setPosition(me::Vector3 pos)
{
	mPosition = pos;
}

void CircuitInfo::setInfo(float halfWidthInner, float halfWidthOuter, float halfHeightInner, float halfHeightOuter, float radiusInner, float radiusOuter)
{
	mHalfHeightInner = halfHeightInner;
	mHalfHeightOuter = halfHeightOuter;
	mHalfWidthInner = halfWidthInner;
	mHalfWidthOuter = halfWidthOuter;
	mRadiusInner = radiusInner;
	mRadiusOuter = radiusOuter;
}

void CircuitInfo::setLaps(int laps)
{
	mLaps = laps;
}

int CircuitInfo::getLaps()
{
	return mLaps;
}

void CircuitInfo::setDeathHeight(float deathHeight)
{
	mDeathHeight = deathHeight;
}

float CircuitInfo::getDeathHeight()
{
	return mDeathHeight;
}

void CircuitInfo::startRace()
{
	mTimer->resume();
}

std::string CircuitInfo::getFinishTime()
{
	return mTimer->getFormattedTime();
}
