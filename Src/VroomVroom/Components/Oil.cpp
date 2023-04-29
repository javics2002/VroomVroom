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

void Oil::onCollisionEnter(me::Entity* other)
{
	if (other->getName() == "carone" || other->getName() == "cartwo") {
		// Save the player's current friction value to be restored later
		mPlayerFriction = other->getComponent<me::RigidBody>("Rigidbody")->getFriction();
		other->getComponent<me::RigidBody>("Rigidbody")->setFriction(mFriction);
	}
}

void Oil::onCollisionStay(me::Entity* other)
{
	if (other->getName() == "carone" || other->getName() == "cartwo") {
		// Apply the oil's friction to the player
		other->getComponent<me::RigidBody>("Rigidbody")->setFriction(mFriction);
	}
}

void Oil::onCollisionExit(me::Entity* other)
{
	if (other->getName() == "carone" || other->getName() == "cartwo") {
		// Restore the player's previous friction value
		other->getComponent<me::RigidBody>("Rigidbody")->setFriction(mPlayerFriction);
		// Destroy the oil object from the scene
		//mEntity->destroy();
	}
	
}

void VroomVroom::Oil::use(me::Entity* other)
{

	me::Vector3 v = other->getComponent<Transform>("transform")->getPosition();
	me::Vector3 offset(-2, 2, 0);

	mEntity->getComponent<RigidBody>("rigidbody")->activeBody();
	mEntity->getComponent<MeshRenderer>("meshrenderer")->activeMesh();
	//mEntity->getComponent<Transform>("transform")->setPosition(v +offset);

}
