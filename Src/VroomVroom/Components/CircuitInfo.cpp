#include "CircuitInfo.h"
#include "MotorEngine/Scene.h"
#include "EntityComponent/Entity.h"
#include "MotorEngine/SceneManager.h"
#include "EntityComponent/Transform.h"
#include "Audio/SoundManager.h"
#include "VehicleController.h"
#include "Checkpoint.h"
#include "GameManager.h"
#include "MotorEngine/MotorEngineError.h"
#include "Utils/Timer.h"
#include "Render/UIComponents/UISpriteRenderer.h"

#define _USE_MATH_DEFINES
#include <math.h>
#include <chrono>

using namespace me;
using namespace VroomVroom;


Component* FactoryCirtuitInfo::create(Parameters& params)
{
	CircuitInfo* circuitInfo = new CircuitInfo();
	circuitInfo->setPosition(Vector3(Value(params, "position_x", 0.0f),
		Value(params, "position_y", 0.0f), Value(params, "position_z", 0.0f)));

	circuitInfo->setLaps(Value(params, "laps", 3));

	circuitInfo->setInfo(Value(params, "halfwidthinner", 36.0f), Value(params, "halfwidthouter", 44.0f),
		Value(params, "halfheightinner", 1.7f), Value(params, "halfheightouter", 8.0f),
		Value(params, "radiusinner", 1.7f), Value(params, "radiusouter", 8.0f));

	return circuitInfo;
}

void FactoryCirtuitInfo::destroy(Component* component)
{
	delete component;
}

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

	Entity* countdownEntity = sceneManager().getActiveScene()->findEntity("countdownui").get();
	if (!countdownEntity) {
		errorManager().throwMotorEngineError("CircuitInfo error", "CountdownUI entity was not found");
		sceneManager().quit();
		return;
	}

	mCountdownSprite = countdownEntity->getComponent<UISpriteRenderer>("uispriterenderer");

	if (!mCountdownSprite) {
		errorManager().throwMotorEngineError("CircuitInfo error", "CountdownUI entity doesn't have UISpriteRenderer component");
		sceneManager().quit();
        return;
	}

}

void CircuitInfo::update(const double& dt)
{
	mTimer->update(dt);

	if (gameManager() == nullptr) {
		errorManager().throwMotorEngineError("CircuitInfo Update Error", "Game Manager does not exist");
		sceneManager().quit();
		return;
	}

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
				Entity* entity = mCheckpoints[(mVehicles[i]->getChekpointIndex() + 1) % Checkpoint::GetNumCheckpoints()]
					->getEntity();
				if (!entity) {
					errorManager().throwMotorEngineError("CalculatePlaces error", 
						"Checkpoint" + std::to_string((mVehicles[i]->getChekpointIndex() + 1) 
							% Checkpoint::GetNumCheckpoints()) + " entity was not found.");
					sceneManager().quit();
					return;
				}
				Transform* transform = entity->getComponent<Transform>("transform");
				if (!transform) {
					errorManager().throwMotorEngineError("CalculatePlaces error",
						entity->getName() + " entity doesn't have transform component.");
					sceneManager().quit();
					return;
				}
				Vector3 nextCheckpointPosition = transform->getPosition();
					
				Entity* iVehicleEntity = mVehicles[i]->getEntity();
				if (!iVehicleEntity) {
					errorManager().throwMotorEngineError("CalculatePlaces error",
						std::to_string(i) + " vehicle entity was not found.");
					sceneManager().quit();
					return;
				}
				Transform* iVehicleTransform = iVehicleEntity->getComponent<Transform>("transform");
				if (!iVehicleTransform) {
					errorManager().throwMotorEngineError("CalculatePlaces error",
						std::to_string(i) + " vehicle entity doesn't have transform component.");
					sceneManager().quit();
					return;
				}
				Vector3 iVehiclePosition = iVehicleTransform->getPosition();


				Entity* jVehicleEntity = mVehicles[j]->getEntity();
				if (!iVehicleEntity) {
					errorManager().throwMotorEngineError("CalculatePlaces error",
						std::to_string(j) + " vehicle entity was not found.");
					sceneManager().quit();
					return;
				}
				Transform* jVehicleTransform = jVehicleEntity->getComponent<Transform>("transform");
				if (!jVehicleTransform) {
					errorManager().throwMotorEngineError("CalculatePlaces error",
						std::to_string(j) + " vehicle entity doesn't have transform component.");
					sceneManager().quit();
					return;
				}
				Vector3 jVehiclePosition = jVehicleTransform->getPosition();

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

		Entity* placeEntity = getEntity()->getScene()->findEntity(placeUIName).get();
		if (!placeEntity) {
			errorManager().throwMotorEngineError("CalculatePlaces error",
				placeUIName + " entity was not found.");
			sceneManager().quit();
			return;
		}
		UISpriteRenderer* placeUISprite = placeEntity->getComponent<UISpriteRenderer>("uispriterenderer");
		if (!placeUISprite) {
			errorManager().throwMotorEngineError("CalculatePlaces error",
				placeUIName + " entity doesn't have UISpriteRenderer component.");
			sceneManager().quit();
			return;
		}

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
