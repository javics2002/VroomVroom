#include "Nerf.h"
#include "VehicleController.h"
#include "EntityComponent/Components/Transform.h"
#include "EntityComponent/Components/RigidBody.h"
#include "EntityComponent/Components/MeshRenderer.h"
#include "EntityComponent/Components/AudioSource.h"
#include "EntityComponent/Entity.h"
#include "Utils/Timer.h"
#include <iostream>

using namespace me;
using namespace VroomVroom;

Nerf::Nerf()
{
	mRigidBody = nullptr;
	mTransform = nullptr;
	mLostControl = 0;
	mSpeed = 3;
	mHit = false;
	mHitCar = nullptr;
}

Nerf::~Nerf()
{
	delete mTimer;
}

void Nerf::start()
{
	mTimer = new Timer(false);
	mTransform = mEntity->getComponent<Transform>("transform");
	mRigidBody = mEntity->getComponent<RigidBody>("rigidbody");
}

void Nerf::update(const double& dt)
{
	//vForward = mUsedCar->getComponent<Transform>("transform")->forward();
	Vector3 test = mTransform->forward().normalize() * mSpeed;
	// std::cout << test.x << " " << test.y << " " << test.z << "\n";
	mTransform->translate(mTransform->forward().normalize() * mSpeed * dt);
	std::cout << "NerfPos: " << mTransform->getPosition().x << " " << mTransform->getPosition().y << " " << mTransform->getPosition().z << "\n";
}

void VroomVroom::Nerf::setSpeed(float speed)
{
	mSpeed = speed;
}

void VroomVroom::Nerf::setLostControl(float lost)
{
	mLostControl = lost;
}

void Nerf::onCollisionEnter(me::Entity* other)
{
	std::cout << "Colisiono con " << other->getName() << "\n";
	if (other->hasComponent("vehiclecontroller")) {
		mHit = true;
		mHitCar = other;
		mHitCar->getComponent<VehicleController>("vehiclecontroller")->startNerfTimer();
	}

	if(!other->hasComponent("checkpoint") && !other->hasComponent("oil") && !other->hasComponent("powerupobject"))
		//Desactivo rigidbody etc o lo mando a tomar por culo.
		mEntity->destroy();
}

void Nerf::use(me::Entity* other)
{
	mNerfSound = mEntity->getComponent<AudioSource>("audiosource");
	mNerfSound->play();

	Transform* carTr = other->getComponent<Transform>("transform");

	mTransform->setPosition(carTr->getPosition() + (carTr->forward().normalize() * 3));
	mTransform->setRotation(carTr->getRotation());

	mUsedCar = other;

	std::cout << "CarPos: " << carTr->getPosition().x << " " << carTr->getPosition().y << " " << carTr->getPosition().z << "\n";
	std::cout << "NerfPos: " << mTransform->getPosition().x << " " << mTransform->getPosition().y << " " << mTransform->getPosition().z << "\n";
}


