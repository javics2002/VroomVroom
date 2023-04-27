#include "Nerf.h"
#include "VehicleController.h"
#include "EntityComponent/Components/Transform.h"
#include "EntityComponent/Components/RigidBody.h"
#include "EntityComponent/Entity.h"
#include "Utils/Timer.h"

using namespace me;
using namespace VroomVroom;

Nerf::Nerf()
{
	mRigidBody = nullptr;
	mTransform = nullptr;
	mLostControl = 0;
	mSpeed = 0;
	mHit = false;
	mHitCar = nullptr;
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
	Vector3 carPosition = mUsedCar->getComponent<Transform>("transform")->getPosition();
	mTransform->setPosition(carPosition/* +  offset */);
	vForward = mUsedCar->getComponent<Transform>("transform")->forward();
	mRigidBody->addForce(vForward * mSpeed * dt);

	if (mHit) {
		mTimer->update(dt);
		if (mTimer->getRawSeconds() >= mLostControl) {
			mHitCar->getComponent<VehicleController>("vehiclecontroller")->setControllable(true);
			mHit = false;
			mHitCar = nullptr;
		}
	}
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
	if (other->getName() == "car") {
		mHit = true;
		mHitCar = other;
		mHitCar->getComponent<VehicleController>("vehiclecontroller")->setControllable(false);
	}
	//Desactivo rigidbody etc o lo mando a tomar por culo.
}

void Nerf::use(me::Entity* other)
{
	mUsedCar = other;
	/*vForward = other->getComponent<Transform>("transform")->forward();
	mCarPosition = other->getComponent<Transform>("transform")->getPosition();*/
}


