#include "Oil.h"
#include "EntityComponent/Components/RigidBody.h"
#include "EntityComponent/Entity.h"

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
	// Save the player's current friction value to be restored later
	mPlayerFriction = other->getComponent<me::RigidBody>("Rigidbody")->getFriction();
	other->getComponent<me::RigidBody>("Rigidbody")->setFriction(mFriction);
	
}

void Oil::onCollisionStay(me::Entity* other)
{
	// Apply the oil's friction to the player
	other->getComponent<me::RigidBody>("Rigidbody")->setFriction(mFriction);
}

void Oil::onCollisionExit(me::Entity* other)
{
	// Restore the player's previous friction value
	other->getComponent<me::RigidBody>("Rigidbody")->setFriction(mPlayerFriction);
	// Destroy the oil object from the scene
	mEntity->destroy();
}
