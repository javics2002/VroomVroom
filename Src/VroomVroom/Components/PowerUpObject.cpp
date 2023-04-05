#include "PowerUpObject.h"
#include "Oil.h"
#include <math.h>
#include "VehicleController.h"
#include "EntityComponent/Components/MeshRenderer.h"
#include "EntityComponent/Components/Rigidbody.h"

using namespace me;

PowerUpObject::PowerUpObject()
{
}

PowerUpObject::~PowerUpObject()
{
}

void PowerUpObject::start()
{
	// Choose a random power-up type when the object is spawned
	mPowerUp = PowerUpType(rand() % 3);
	mReviveTime = 10000; // Set the time it takes for the power-up object to respawn after being picked up
}

void PowerUpObject::update()
{
	if (mPicked) {
		mTime += 1; // Increase the elapsed time since the power-up was picked up by delta time
		if (mTime >= mReviveTime) {

			// Reactivate the MeshRenderer and RigidBody components of the power-up object after the respawn time has elapsed
			mEntity->getComponent<MeshRenderer>("meshrenderer")->enabled = true; // Activamos de nuevo el componente MeshRenderer
			mEntity->getComponent<RigidBody>("rigidbody")->enabled = true;

			mPicked = false; // Reset the picked flag to allow the power-up object to be picked up again
 			mTime = 0; // Reset the elapsed time since the power-up was picked up

			resetPowerUp(); // Choose a new random power-up type for the object to represent
		}
	}
}

void PowerUpObject::resetPowerUp()
{
	// Choose a new random power-up type for the object to represent
	mPowerUp = PowerUpType(rand() % 3);
}

void PowerUpObject::onCollisionEnter(Entity* other)
{
	// Deactivate the MeshRenderer and RigidBody components of the power-up object when it is picked up by a player
	mEntity->getComponent<MeshRenderer>("meshrenderer")->enabled = false; // Desactivamos el MeshRenderer para que no se vea por pantalla
	mEntity->getComponent<RigidBody>("rigidbody")->enabled = false; // Desactivamos las colisiones

	// Pass the power-up type to the player's vehicle controller component
	other->getComponent<VehicleController>("vehiclecontroller")->setPowerUp(mPowerUp);
	mPicked = true;

	//TODO: ACTIVATE THE SPIN ANIMATION OF THE UI ROULETTE

}
