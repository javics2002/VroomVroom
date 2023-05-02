#include "Nerf.h"
#include "VehicleController.h"
#include "EntityComponent/Components/Transform.h"
#include "EntityComponent/Components/RigidBody.h"
#include "EntityComponent/Components/MeshRenderer.h"
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
	isActive = false;
}

Nerf::~Nerf()
{
}

void Nerf::start()
{
	mTimer = new Timer(false);
	mTransform = mEntity->getComponent<Transform>("transform");
	mRigidBody = mEntity->getComponent<RigidBody>("rigidbody");
}

void Nerf::update(const double& dt)
{
	if (!isActive)
		return;

	//vForward = mUsedCar->getComponent<Transform>("transform")->forward();
	Vector3 test = mTransform->forward().normalize() * mSpeed;
	// std::cout << test.x << " " << test.y << " " << test.z << "\n";
	mRigidBody->setVelocity(test);

	/*if (mHit) {
		mTimer->update(dt);
		if (mTimer->getRawSeconds() >= mLostControl) {
			mHitCar->getComponent<VehicleController>("vehiclecontroller")->setControllable(true);
			mHit = false;
			mHitCar = nullptr;
		}
	}*/
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
	if (other->getName() == "carone" || other->getName() == "cartwo") {
		mHit = true;
		mHitCar = other;
		mHitCar->getComponent<VehicleController>("vehiclecontroller")->setControllable(false);
		
	}
	//Desactivo rigidbody etc o lo mando a tomar por culo.
	mEntity->getComponent<MeshRenderer>("meshrenderer")->desactiveMesh(); // Desactivamos el MeshRenderer para que no se vea por pantalla
	mEntity->getComponent<RigidBody>("rigidbody")->desactiveBody();
}

void Nerf::use(me::Entity* other)
{
	Transform* carTr = other->getComponent<Transform>("transform");
	Transform* tr = mEntity->getComponent<Transform>("transform");

	tr->setPosition(carTr->getPosition() + (carTr->forward().normalize() * 3));
	me::Vector3 posNerf = tr->getPosition();
	posNerf.y = carTr->getPosition().y;
	tr->setPosition(posNerf);

	mUsedCar = other;

	isActive = true;
	//vForward = mUsedCar->getComponent<Transform>("transform")->forward();
	/*mCarPosition = other->getComponent<Transform>("transform")->getPosition();*/
}


