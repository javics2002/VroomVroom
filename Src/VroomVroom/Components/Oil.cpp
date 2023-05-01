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
		// Save the player's current friction value to be restored later
		mPlayerFriction = other->getComponent<me::RigidBody>("rigidbody")->getFriction();
		other->getComponent<me::RigidBody>("rigidbody")->setFriction(mFriction);
	}
}

void Oil::onCollisionStay(me::Entity* other)
{
	if (other->getName() == "carone" || other->getName() == "cartwo") {
		// Apply the oil's friction to the player
		other->getComponent<me::RigidBody>("rigidbody")->setFriction(mFriction);
	}
}

void Oil::onCollisionExit(me::Entity* other)
{
	if (other->getName() == "carone" || other->getName() == "cartwo") {
		// Restore the player's previous friction value
		other->getComponent<me::RigidBody>("rigidbody")->setFriction(mPlayerFriction);
		// Destroy the oil object from the scene
		mEntity->destroy();
	}
	
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
