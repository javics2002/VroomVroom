#include "Nerf.h"

#include "VehicleController.h"
#include "EntityComponent/Transform.h"
#include "Audio/AudioComponents/AudioSource.h"
#include "EntityComponent/Entity.h"
#include "Utils/Timer.h"
#include "MotorEngine/MotorEngineError.h"
#include "MotorEngine/SceneManager.h"

using namespace me;
using namespace VroomVroom;

me::Component* VroomVroom::FactoryNerf::create(me::Parameters& params)
{
	Nerf* nerf = new Nerf();
	return nerf;
}

void VroomVroom::FactoryNerf::destroy(me::Component* component)
{
	delete component;
}


Nerf::Nerf()
{
	mSpeed = 3;
}

Nerf::~Nerf()
{
	delete mTimer;
}

void Nerf::start()
{
	mTimer = new Timer(false);
}

void Nerf::update(const double& dt)
{
	Transform* transform = mEntity->getComponent<Transform>("transform");
	if (!transform) {
		errorManager().throwMotorEngineError("Nerf update error",
			"nerf entity doesn't have transform component.");
		sceneManager().quit();
		return;
	}
	transform->translate(transform->forward().normalize() * mSpeed * dt);
}

void Nerf::setSpeed(float speed)
{
	mSpeed = speed;
}

void Nerf::onCollisionEnter(Entity* other)
{
	if (other->hasComponent("vehiclecontroller"))
		other->getComponent<VehicleController>("vehiclecontroller")->startNerfTimer();

	mEntity->destroy();
}

void Nerf::use(Entity* other)
{
	mNerfSound = mEntity->getComponent<AudioSource>("audiosource");
	if (!mNerfSound) {
		errorManager().throwMotorEngineError("Nerf use error",
			"nerf entity doesn't have audioSource component.");
		sceneManager().quit();
		return;
	}
	mNerfSound->play();

	Transform* carTr = other->getComponent<Transform>("transform");
	if (!carTr) {
		errorManager().throwMotorEngineError("Nerf use error",
			other->getName() + " entity doesn't have transform component.");
		sceneManager().quit();
		return;
	}

	Transform* transform = mEntity->getComponent<Transform>("transform");
	if (!transform) {
		errorManager().throwMotorEngineError("Nerf use error",
			"nerf entity doesn't have transform component.");
		sceneManager().quit();
		return;
	}
	transform->setPosition(carTr->getPosition() + (carTr->forward().normalize() * 3));
	transform->setRotation(carTr->getRotation());
}


