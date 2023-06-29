#include "Thief.h"

#include "VehicleController.h"
#include "EntityComponent/Transform.h"
#include "Audio/AudioComponents/AudioSource.h"
#include "PowerUpUIWheel.h"
#include "EntityComponent/Entity.h"
#include "Utils/Timer.h"
#include "MotorEngine/MotorEngineError.h"
#include "MotorEngine/SceneManager.h"

using namespace me;
using namespace VroomVroom;

me::Component* VroomVroom::FactoryThief::create(me::Parameters& params)
{
	Thief* thief = new Thief();
	return thief;
}

void VroomVroom::FactoryThief::destroy(me::Component* component)
{
	delete component;
}


Thief::Thief()
{
	mSpeed = 3;
}

Thief::~Thief()
{
	delete mTimer;
}

void Thief::start()
{
	mTimer = new Timer(false);
}

void Thief::update(const double& dt)
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

void Thief::setSpeed(float speed)
{
	mSpeed = speed;
}

void Thief::onCollisionEnter(Entity* other)
{
	Entity* stolenPowerUp;

	if (other->hasComponent("vehiclecontroller")) {
		VehicleController* otherVC = other->getComponent<VehicleController>("vehiclecontroller");
		VehicleController* myVC = mEntity->getComponent<VehicleController>("vehiclecontroller");
		stolenPowerUp = other->getComponent<VehicleController>("vehiclecontroller")->getPowerUpStolen();

		if (stolenPowerUp != nullptr) {
			myVC->setPowerUp(otherVC->getPowerUpType(), stolenPowerUp);
			std::string name;
			switch (otherVC->getPowerUpType())
			{
			case 0:
				name = "nerf";
				break;
			case 1:
				name = "oil";
				break;
			case 2:
				name = "lightningBolt";
				break;
			case 3:
				name = "thief";
				break;
			}
			mEntity->getComponent<PowerUpUIWheel>("powerupuiwheel")->stopSpinOnSprite(name);
		}
	}
	mEntity->destroy();
}

void Thief::use(Entity* other)
{
	mThiefSound = mEntity->getComponent<AudioSource>("audiosource");
	if (!mThiefSound) {
		errorManager().throwMotorEngineError("Nerf use error",
			"nerf entity doesn't have audioSource component.");
		sceneManager().quit();
		return;
	}
	mThiefSound->play();

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