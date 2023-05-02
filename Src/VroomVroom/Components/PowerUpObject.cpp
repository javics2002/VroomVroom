#include "PowerUpObject.h"
#include "Oil.h"
#include "Nerf.h"
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
	if ((other->getName() == "carone" || other->getName() == "cartwo")) {

		// Deactivate the MeshRenderer and RigidBody components of the power-up object when it is picked up by a player
		mEntity->getComponent<MeshRenderer>("meshrenderer")->desactiveMesh(); // Desactivamos el MeshRenderer para que no se vea por pantalla
		mEntity->getComponent<RigidBody>("rigidbody")->desactiveBody(); // Desactivamos las colisiones
		mPicked = true;
		mTimer->resume();

		if (!other->getComponent<VehicleController>("vehiclecontroller")->isPowerUpPicked()) {
			switch (mPowerUp)
			{
			case NERF:
				mPowerUpEntity = createNerfEntity();
				break;
			case OIL:
				mPowerUpEntity = createOilEntity();
				break;
			}

			other->getComponent<VehicleController>("vehiclecontroller")->setPowerUp(mPowerUp, mPowerUpEntity);
			other->getComponent<VehicleController>("vehiclecontroller")->setPowerUpUI();

		}
	}
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
	tr->setPosition(me::Vector3(-70,-100,-10));
	tr->setRotation(me::Vector3(0, 0, 0));
	tr->setScale(me::Vector3(6, 1, 6));

	col = oil->addComponent<me::Collider>("collider");

	rb = oil->addComponent<me::RigidBody>("rigidbody");
	rb->setColShape(SHAPES_BOX);
	rb->setMomeventType(MOVEMENT_TYPE_KINEMATIC);
	rb->setMass(1);
	rb->setGroup(1);
	rb->setMask(6);
	rb->setColliderScale(me::Vector3(0.25,1,0.25));
	rb->setRestitution(0.5);
	rb->setFriction(0.5);
	rb->setTrigger(true);

	mesh = oil->addComponent<me::MeshRenderer>("meshrenderer");
	mesh->setMeshName("Oil.mesh");
	mesh->setName("o" + std::to_string(gameManager()->getContPowerUps()));
	mesh->init();

	o = oil->addComponent<Oil>("oil");
	o->setFriction(2);
	o->setOffset(3);
	o->setPosYOil(5.2);

	gameManager()->addPowerUp();

	return oil;
}

me::Entity* VroomVroom::PowerUpObject::createNerfEntity()
{
	me::Entity* nerf = mEntity->getScene()->addEntity("Nerf" + std::to_string(gameManager()->getContPowerUps())).get();
	me::Transform* tr;
	me::RigidBody* rb;
	me::Collider* col;
	me::MeshRenderer* mesh;
	Nerf* n;

	tr = nerf->addComponent<me::Transform>("transform");
	tr->setPosition(me::Vector3(-70, -90, -10));
	tr->setRotation(me::Vector3(0, 0, 0));
	tr->setScale(me::Vector3(1, 1, 1));

	col = nerf->addComponent<me::Collider>("collider");

	rb = nerf->addComponent<me::RigidBody>("rigidbody");
	rb->setColShape(SHAPES_BOX);
	rb->setMomeventType(MOVEMENT_TYPE_DYNAMIC);
	rb->setMass(1);
	rb->setGroup(1);
	rb->setMask(6);
	rb->setColliderScale(me::Vector3(1, 1, 1));
	rb->setRestitution(0.5);
	rb->setFriction(0.5);
	rb->setTrigger(true);

	mesh = nerf->addComponent<me::MeshRenderer>("meshrenderer");
	mesh->setMeshName("Nerf.mesh");
	mesh->setName("n" + std::to_string(gameManager()->getContPowerUps()));
	mesh->init();

	n = nerf->addComponent<Nerf>("nerf");

	gameManager()->addPowerUp();

	return nerf;
}
