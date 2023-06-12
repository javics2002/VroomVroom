#include "CircuitInfo.h"
#include "MotorEngine/Scene.h"
#include "EntityComponent/Entity.h"
#include "MotorEngine/SceneManager.h"
#include "EntityComponent/Transform.h"
#include "Audio/SoundManager.h"
#include "VehicleController.h"
#include "Checkpoint.h"
#include "GameManager.h"

#include "Utils/Timer.h"
#include "Render/UIComponents/UISpriteRenderer.h"

#define _USE_MATH_DEFINES
#include <math.h>
#include <chrono>

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
	delete mTimer;
	delete mFinishTimer;
}

void CircuitInfo::start()
{
	mRaceStarted = false;
	mTimer = new Timer(true);

	mCountdownSprite = sceneManager().getActiveScene()->findEntity("countdownui").get()
		->getComponent<UISpriteRenderer>("uispriterenderer");

}

void CircuitInfo::update(const double& dt)
{
	mTimer->update(dt);

	if (!mRaceStarted && !mRaceFinished) {
		if (mTimer->getRawSeconds() > 3) {
			mRaceStarted = true;
			//GO!
			mCountdownSprite->setSpriteMaterial("countdownGO");
			mTimer->reset();

			for (VehicleController* vehicle : mVehicles)
				vehicle->setControllable(true);
		}
		else if (mTimer->getRawSeconds() > 2) {
			//1
			mCountdownSprite->setSpriteMaterial("countdown1");
		}
		else if (mTimer->getRawSeconds() > 1) {
			//2
			mCountdownSprite->setSpriteMaterial("countdown2");
		}
		else {
			//3
			mCountdownSprite->setSpriteMaterial("countdown3");
		}

		return;
	}
	else if (mRaceStarted && !mRaceFinished) {
		if (mTimer->getRawSeconds() > 1 && mCountdownSprite != nullptr) {
			mCountdownSprite->getEntity()->destroy();
			mCountdownSprite = nullptr;
		}

		if (gameManager()->getNumPlayer() == 2)
			calculatePlaces();
	}
	else if (mRaceFinished && mRaceStarted) {
		mFinishTimer->update(dt);
		if (mFinishTimer->getRawSeconds() > 3) {
			if (gameManager()->getNumPlayer() > 1) {
				sceneManager().change("resultstwo.lua");
				soundManager().stopEverySound();
				gameManager()->changeState("resultstwo.lua");
			}
			else {
				sceneManager().change("results.lua");
				soundManager().stopEverySound();
				gameManager()->changeState("results.lua");
			}
		}
	}
	
}

void CircuitInfo::calculatePlaces()
{
	//Reset all vehicles to first place and then push them back one by one
	for (VehicleController* vehicle : mVehicles)
		vehicle->setPlace(1);

	for (int i = 0; i < mVehicles.size(); i++) 
		for (int j = i + 1; j < mVehicles.size(); j++) 
			//First check their lap
			if (mVehicles[i]->getLap() < mVehicles[j]->getLap())
				//i is behind
				mVehicles[i]->setPlace(mVehicles[i]->getPlace() + 1);
			else if (mVehicles[i]->getLap() > mVehicles[j]->getLap())
				//j is behind
				mVehicles[j]->setPlace(mVehicles[j]->getPlace() + 1);

			//Then check their checkpoint
			else if (mVehicles[i]->getChekpointIndex() < mVehicles[j]->getChekpointIndex())
				//i is behind
				mVehicles[i]->setPlace(mVehicles[i]->getPlace() + 1);
			else if (mVehicles[i]->getChekpointIndex() > mVehicles[j]->getChekpointIndex())
				//j is behind
				mVehicles[j]->setPlace(mVehicles[j]->getPlace() + 1);

			//Lastly check their remaining distance to the next checkpoint
			else {
				Vector3 nextCheckpointPosition =
					mCheckpoints[(mVehicles[i]->getChekpointIndex() + 1) % Checkpoint::GetNumCheckpoints()]
					->getEntity()->getComponent<Transform>("transform")->getPosition();

				Vector3 iVehiclePosition = mVehicles[i]->getEntity()
					->getComponent<Transform>("transform")->getPosition();
				Vector3 jVehiclePosition = mVehicles[j]->getEntity()
					->getComponent<Transform>("transform")->getPosition();

				if (nextCheckpointPosition.distance(iVehiclePosition)
					> nextCheckpointPosition.distance(jVehiclePosition))
					//i is behind
					mVehicles[i]->setPlace(mVehicles[i]->getPlace() + 1);
				else
					//j is behind
					mVehicles[j]->setPlace(mVehicles[j]->getPlace() + 1);
			}

	//Update UI place
	for (VehicleController* vehicle : mVehicles) {
		EntityName placeUIName;
		switch (vehicle->getPlayerNumber()) {
		case PLAYERNUMBER_1:
			placeUIName = "place1";
			break;
		case PLAYERNUMBER_2:
			placeUIName = "place2";
			break;
		default:
			continue;
		}

		UISpriteRenderer* placeUISprite = getEntity()->getScene()->findEntity(placeUIName).get()
			->getComponent<UISpriteRenderer>("uispriterenderer");

		switch (vehicle->getPlace()) {
		case 1:
			placeUISprite->setSpriteMaterial("first");
			break;
		case 2:
			placeUISprite->setSpriteMaterial("second");
			break;
		default:
			break;
		}
	}
}

bool CircuitInfo::isCircuitInside(Vector3 pos)
{
	// pos.z must be inside (8 , 1.7) || (-1.7 , -8)  vertical
	// Case (-1.7 , 1.7) if pos.x be inside (-36 , 36)

	if (pos.z > mPosition.z + mHalfHeightOuter ||
		pos.z < mPosition.z - mHalfHeightOuter ||
		(pos.z > mPosition.z - mHalfHeightInner && pos.z < mPosition.z + mHalfHeightInner
			&& pos.x > mPosition.x - mHalfWidthInner && pos.x < mPosition.x + mHalfHeightInner))
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
	Vector3 pointLeft = Vector3(mPosition.x - mHalfWidthInner, mPosition.y, mPosition.z);
	Vector3 pointRight = Vector3(mPosition.x + mHalfWidthInner, mPosition.y, mPosition.z);

	Vector3 dist;
	float distance;
	// if pos.x is in (36 , 44)
	if (pos.x > mPosition.x + mHalfWidthInner) {
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
	float x, z, radius;
	std::srand(std::time(nullptr));

	//range (-44 ,44)
	x = -mHalfWidthOuter + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / (mHalfWidthOuter * 2));

	//range (-36 , 36)
	if (x < mHalfWidthInner || x > -mHalfWidthInner) {
		bool is_negative = rand() % 2 == 0;

		z = static_cast<float>(rand()) / static_cast<float>(RAND_MAX / (mHalfHeightOuter - mHalfHeightInner));

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
			x = mPosition.x + mHalfWidthInner - +x;
		else
			x = mPosition.x - mHalfWidthInner - x;
		z = radius * std::sin(radians) + mPosition.z;
	}

	return Vector3(x, mPosition.y, z);
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


std::string CircuitInfo::getElapsedTime()
{
	return mTimer->getFormattedTime();
}
std::string CircuitInfo::getFinishTime()
{

	if (++mCarsFinished == mVehicles.size()) {

		mRaceFinished = true;
		mTimer->pause();
		mFinishTimer = new Timer(true);
	}

	return mTimer->getFormattedTime();
}

int VroomVroom::CircuitInfo::getCarFinished()
{
	return mCarsFinished;
}

void CircuitInfo::addVehicle(VehicleController* newVehicle)
{
	mVehicles.push_back(newVehicle);
}

void CircuitInfo::addCheckpoint(Checkpoint* newCheckpoint)
{
	mCheckpoints[newCheckpoint->getIndex()] = newCheckpoint;
}
