#include "Oil.h"
#include "EntityComponent/Components/RigidBody.h"
#include "EntityComponent/Components/MeshRenderer.h"
#include "EntityComponent/Components/AudioSource.h"
#include "VehicleController.h"
#include "EntityComponent/Entity.h"

#include "EntityComponent/Components/Transform.h"

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

void VroomVroom::Oil::setOffset(float offset)
{
	mOffset = offset;
}

void VroomVroom::Oil::setPosYOil(float posYOil)
{
	mPosYOil = posYOil;
}

void Oil::onCollisionEnter(me::Entity* other)
{
	if (other->hasComponent("vehiclecontroller")) {
		VehicleController* vehiclecontroller = other->getComponent<VroomVroom::VehicleController>("vehiclecontroller");
		// Reduce player's velocity
		float maxSpeed = vehiclecontroller->getOrigMaxSpeed();
		float maxAngularSpeed = vehiclecontroller->getMaxAngularSpeed();
		vehiclecontroller->setMaxSpeedAndRotationSpeed(maxSpeed / 2, maxAngularSpeed);
		vehiclecontroller->startOilTimer();
	}
}

void Oil::onCollisionStay(me::Entity* other)
{
}

void Oil::onCollisionExit(me::Entity* other)
{
	if (other->hasComponent("vehiclecontroller"))
		mEntity->destroy();
}

void VroomVroom::Oil::use(me::Entity* other)
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
