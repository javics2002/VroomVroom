#include "PowerUpObject.h"
#include "Oil.h"
#include <math.h>
#include "VehicleController.h"
#include "Utils/Timer.h"
#include "EntityComponent//Components/Transform.h"
#include "EntityComponent/Components/MeshRenderer.h"
#include "EntityComponent/Components/Rigidbody.h"
#include "EntityComponent/Scene.h"
#include "GameManager.h"

using namespace me;
using namespace VroomVroom;

PowerUpObject::PowerUpObject()
{
}

PowerUpObject::~PowerUpObject()
{
	delete mTimer;
}

void PowerUpObject::start()
{
	// Choose a random power-up type when the object is spawned
	//mPowerUp = PowerUpType(rand() % 3);
	mTimer = new Timer(false);
	mTransform = mEntity->getComponent<Transform>("transform");
	mReviveTime = 4; // Set the time it takes for the power-up object to respawn after being picked up
	mPowerUpEntity = nullptr;
}

void PowerUpObject::update(const double& dt)
{

	if (mPicked) {
		mTimer->update(dt);
		if (mTimer->getRawSeconds() >= mReviveTime) {

			// Reactivate the MeshRenderer and RigidBody components of the power-up object after the respawn time has elapsed
			mEntity->getComponent<MeshRenderer>("meshrenderer")->activeMesh(); // Activamos de nuevo el componente MeshRenderer
			mEntity->getComponent<RigidBody>("rigidbody")->activeBody();

			mPicked = false; // Reset the picked flag to allow the power-up object to be picked up again
			mTimer->reset();

			resetPowerUp(); // Choose a new random power-up type for the object to represent
		}
	}

	else mTransform->rotate(1, me::Vector3(0,1,0));
}

void PowerUpObject::resetPowerUp()
{
	// Choose a new random power-up type for the object to represent
	mPowerUp = PowerUpType(rand() % 3);
}

void PowerUpObject::setPower(PowerUpType type)
{
	mPowerUp = type;
}

void PowerUpObject::onCollisionEnter(me::Entity* other)
{

	// Pass the power-up type to the player's vehicle controller component
	if (other->getName() == "car"){
		// Deactivate the MeshRenderer and RigidBody components of the power-up object when it is picked up by a player
		mEntity->getComponent<MeshRenderer>("meshrenderer")->desactiveMesh(); // Desactivamos el MeshRenderer para que no se vea por pantalla
		mEntity->getComponent<RigidBody>("rigidbody")->desactiveBody(); // Desactivamos las colisiones
		
		switch (mPowerUp)
		{
		case NERF:
			break;
		case OIL:
			mPowerUpEntity = createOilEntity();
			break;
		}

		other->getComponent<VehicleController>("vehiclecontroller")->setPowerUp(mPowerUp);
		other->getComponent<VehicleController>("vehiclecontroller")->setPowerUpUI();
		mPicked = true;
		mTimer->resume();
		std::cout << "PowerUp picked: " << mPowerUp << std::endl;
	}

	//TODO: ACTIVATE THE SPIN ANIMATION OF THE UI ROULETTE

}

me::Entity* VroomVroom::PowerUpObject::createOilEntity()
{
	me::Entity* oil = mEntity->getScene()->addEntity("Oil" + std::to_string(gameManager()->getContPowerUps())).get();
	me::Transform* tr;
	me::RigidBody* rb;
	me::Collider* col;
	me::MeshRenderer* mesh;
	Oil* o;

	tr = oil->addComponent<me::Transform>("transform");
	tr->setPosition(me::Vector3(0,6,0));
	tr->setRotation(me::Vector3(0, 0, 0));
	tr->setScale(me::Vector3(0.5, 0.5, 0.5));

	col = oil->addComponent<me::Collider>("collider");

	rb = oil->addComponent<me::RigidBody>("rigidbody");
	rb->setColShape(SHAPES_BOX);
	rb->setMomeventType(MOVEMENT_TYPE_DYNAMIC);
	rb->setMass(1);
	rb->setGroup(2);
	rb->setMask(7);
	rb->setColliderScale(me::Vector3(4, 2, 4));
	rb->setRestitution(0.5);
	rb->setFriction(0.5);
	rb->setTrigger(false);
	rb->desactiveBody();

	mesh = oil->addComponent<me::MeshRenderer>("meshrenderer");
	mesh->setMeshName("Kart.mesh");
	mesh->setName("o" + std::to_string(gameManager()->getContPowerUps()));
	mesh->desactiveMesh();

	o = oil->addComponent<Oil>("oil");
	o->setFriction(2);

	gameManager()->addPowerUp();

	return oil;
}

me::Entity* VroomVroom::PowerUpObject::createNerfEntity()
{
	return nullptr;
}
