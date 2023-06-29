#include "TimeFreezeRing.h"

#include "EntityComponent/Entity.h"
#include "EntityComponent/Transform.h"
#include "Audio/AudioComponents/AudioSource.h"
#include "MotorEngine/Scene.h"
#include "MotorEngine/SceneManager.h"
#include "MotorEngine/MotorEngineError.h"
#include "VehicleController.h"
#include "CircuitInfo.h"

#include <iostream>
#include <cassert>

using namespace me;
using namespace VroomVroom;

me::Component* VroomVroom::FactoryTimeFreezeRing::create(me::Parameters& params)
{
	TimeFreezeRing* timeFreezeRing = new TimeFreezeRing();
	timeFreezeRing->setFreezeSecs(Value(params, "freezesecs", 1.0f));

	std::string circuitInfo = Value(params, "circuitinfoname", std::string("Circuit"));
	timeFreezeRing->setCircuitInfoName(circuitInfo);

	return timeFreezeRing;
}

void VroomVroom::FactoryTimeFreezeRing::destroy(me::Component* component)
{
	delete component;
}

TimeFreezeRing::TimeFreezeRing()
{
}

TimeFreezeRing::~TimeFreezeRing()
{
}

void TimeFreezeRing::start()
{
	mTransform = mEntity->getComponent<Transform>("transform");
	if (!mTransform) {
		errorManager().throwMotorEngineError("TimeFreezeRing error", "TimeFreezeRing entity doesn't have transform component");
		sceneManager().quit();
		return;
	}

	mCollisionAudio = mEntity->getComponent<AudioSource>("audiosource");
	if (!mCollisionAudio) {
		errorManager().throwMotorEngineError("TimeFreezeRing error", "TimeFreezeRing entity doesn't have AudioSource component");
		sceneManager().quit();
		return;
	}

	setCircuitInfo();
}

void TimeFreezeRing::onCollisionEnter(me::Entity* other)
{
	if (other->hasComponent("vehiclecontroller")) {

		VehicleController* vehController = other->getComponent<VehicleController>("vehiclecontroller");
		if (!vehController) {
			errorManager().throwMotorEngineError("BoostPad error",
				other->getName() + " entity doesn't have VehicleController component");
			sceneManager().quit();
			return;
		}
		mCollisionAudio->play();

		mCircuitInfo->freezeTimer(mFreezeSecs);
	}
}

void TimeFreezeRing::setFreezeSecs(float secs)
{
	mFreezeSecs = secs;
}

void TimeFreezeRing::setCircuitInfo()
{
	if (!mEntity->getScene()->findEntity(mCircuitInfoName).get()) {
		errorManager().throwMotorEngineError("TimeFreezeRing error", "Circuit entity was not found");
		sceneManager().quit();
		return;
	}


	Entity* circuitEntity = mEntity->getScene()->findEntity(mCircuitInfoName).get();
	if (!circuitEntity) {
		errorManager().throwMotorEngineError("TimeFreezeRing error", "Circuit entity doesn't exist.");
		sceneManager().quit();
		return;
	}

	mCircuitInfo = circuitEntity->getComponent<CircuitInfo>("circuitinfo");

	if (!mCircuitInfo) {
		errorManager().throwMotorEngineError("TimeFreezeRing error", "Circuit entity doesn't have CircuitInfo component");
		sceneManager().quit();
		return;
	}

}

void TimeFreezeRing::setCircuitInfoName(std::string name)
{
	for (char& c : name)
		c = tolower(c);
	mCircuitInfoName = name;
}
