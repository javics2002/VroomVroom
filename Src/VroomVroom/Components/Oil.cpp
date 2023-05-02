#include "Oil.h"
#include "EntityComponent/Components/RigidBody.h"
#include "EntityComponent/Components/MeshRenderer.h"
#include "VehicleController.h"
#include "EntityComponent/Entity.h"

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
	if (other->getName() == "carone" || other->getName() == "cartwo") {
		// Reduce player's velocity
		float maxSpeed = other->getComponent<VroomVroom::VehicleController>("vehiclecontroller")->getOrigMaxSpeed();
		float maxAngularSpeed = other->getComponent<VroomVroom::VehicleController>("vehiclecontroller")->getMaxAngularSpeed();
		other->getComponent<VroomVroom::VehicleController>("vehiclecontroller")->setMaxSpeedAndRotationSpeed(maxSpeed / 2, maxAngularSpeed);
		other->getComponent<VroomVroom::VehicleController>("vehiclecontroller")->startOilTimer();
	}
}

void Oil::onCollisionStay(me::Entity* other)
{
}

void Oil::onCollisionExit(me::Entity* other)
{
	if (other->getName() == "carone" || other->getName() == "cartwo")
		mEntity->destroy();
	
}

void VroomVroom::Oil::use(me::Entity* other)
{

	Transform* carTr = other->getComponent<Transform>("transform");
	Transform *tr = mEntity->getComponent<Transform>("transform");

	tr->setPosition(carTr->getPosition() + (carTr->forward().normalize() * -mOffset));
	me::Vector3 posOil = tr->getPosition();
	posOil.y = mPosYOil;
	tr->setPosition(posOil);
}
