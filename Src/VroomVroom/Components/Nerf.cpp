#include "Nerf.h"

#include "VehicleController.h"
#include "EntityComponent/Transform.h"
#include "Audio/AudioComponents/AudioSource.h"
#include "EntityComponent/Entity.h"
#include "Utils/Timer.h"

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
	mEntity->getComponent<Transform>("transform")->translate(mEntity->getComponent<Transform>("transform")->forward().normalize() * mSpeed * dt);
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
	mNerfSound->play();

	Transform* carTr = other->getComponent<Transform>("transform");

	mEntity->getComponent<Transform>("transform")->setPosition(carTr->getPosition() + (carTr->forward().normalize() * 3));
	mEntity->getComponent<Transform>("transform")->setRotation(carTr->getRotation());
}


