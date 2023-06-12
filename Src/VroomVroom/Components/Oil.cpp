#include "Oil.h"

#include "Audio/AudioComponents/AudioSource.h"
#include "VehicleController.h"
#include "EntityComponent/Entity.h"

#include "EntityComponent/Transform.h"

using namespace me;
using namespace VroomVroom;

Oil::Oil()
{
}

Oil::~Oil()
{
}

void Oil::start()
{
	mFriction = 0;
}

void Oil::setFriction(float friction)
{
	mFriction = friction;
}

void Oil::setOffset(float offset)
{
	mOffset = offset;
}

void Oil::setPosYOil(float posYOil)
{
	mPosYOil = posYOil;
}

void Oil::onCollisionEnter(Entity* other)
{
	if (other->hasComponent("vehiclecontroller")) {
		VehicleController* vehiclecontroller = other->getComponent<VehicleController>("vehiclecontroller");
		// Reduce player's velocity
		float maxSpeed = vehiclecontroller->getOrigMaxSpeed();
		float maxAngularSpeed = vehiclecontroller->getMaxAngularSpeed();
		vehiclecontroller->setMaxSpeedAndRotationSpeed(maxSpeed / 2, maxAngularSpeed);
		vehiclecontroller->startOilTimer();
	}
}

void Oil::onCollisionStay(Entity* other)
{
}

void Oil::onCollisionExit(Entity* other)
{
	if (other->hasComponent("vehiclecontroller"))
		mEntity->destroy();
}

void VroomVroom::Oil::use(Entity* other)
{
	mOilSound = mEntity->getComponent<AudioSource>("audiosource");
	mOilSound->play();
	Transform* carTr = other->getComponent<Transform>("transform");
	Transform *tr = mEntity->getComponent<Transform>("transform");

	tr->setPosition(carTr->getPosition() + (carTr->forward().normalize() * -mOffset));
	me::Vector3 posOil = tr->getPosition();
	posOil.y = mPosYOil;
	tr->setPosition(posOil);
}
