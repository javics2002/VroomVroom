#include "PowerUpObject.h"
#include "Oil.h"
#include "Nerf.h"
#include <math.h>
#include "VehicleController.h"
#include "Utils/Timer.h"
#include "EntityComponent/Entity.h"
#include "EntityComponent/Components/Transform.h"
#include "EntityComponent/Components/MeshRenderer.h"
#include "EntityComponent/Components/Rigidbody.h"
#include "EntityComponent/Components/AudioSource.h"
#include "MotorEngine/Scene.h"
#include "GameManager.h"

#include <iostream>
#include <cassert>

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
	mTakePowerAudio = mEntity->getComponent<AudioSource>("audiosource");
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
	if (other->hasComponent("vehiclecontroller")) {
		// Deactivate the MeshRenderer and RigidBody components of the power-up object when it is picked up by a player
		mEntity->getComponent<MeshRenderer>("meshrenderer")->desactiveMesh(); // Desactivamos el MeshRenderer para que no se vea por pantalla
		mEntity->getComponent<RigidBody>("rigidbody")->desactiveBody(); // Desactivamos las colisiones
		mPicked = true;
		mTimer->resume();
		
		if (!other->getComponent<VehicleController>("vehiclecontroller")->isPowerUpPicked()) {
			mTakePowerAudio->play();
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

Entity* PowerUpObject::createOilEntity()
{
    Entity* oil = mEntity->getScene()->addEntity("Oil" + std::to_string(gameManager()->getContPowerUps())).get();
	Transform* tr;
	RigidBody* rb;
	Collider* col;
	MeshRenderer* mesh;
	AudioSource* audio;
	Oil* o;

	tr = oil->addComponent<Transform>("transform");
	assert(tr);
	tr->setPosition(Vector3(-70,-100,-10));
	tr->setRotation(Vector3(0, 0, 0));
	tr->setScale(Vector3(3, 1, 3));

	col = oil->addComponent<Collider>("collider");
	assert(col);

	audio = oil->addComponent<AudioSource>("audiosource");
	assert(audio);
	audio->setSourceName("oilSound" + std::to_string(gameManager()->getContPowerUps()));
	audio->setSourcePath("throwOil.mp3");
	audio->setPlayOnStart(false);
	audio->setGroupChannelName("effects");
	audio->setVolume(4.0f);
	audio->setIsThreeD(true);
	audio->setLoop(false);
	audio->setMinDistance(1.0f);
	audio->setMaxDistance(60.0f);

	rb = oil->addComponent<RigidBody>("rigidbody");
	assert(rb);
	rb->setColShape(SHAPES_BOX);
	rb->setMomeventType(MOVEMENT_TYPE_KINEMATIC);
	rb->setMass(1);
	rb->setGroup(6);
	rb->setMask(1);
	rb->setColliderScale(Vector3(0.25,1,0.25));
	rb->setRestitution(0.5);
	rb->setFriction(0.5);
	rb->setTrigger(true);

	mesh = oil->addComponent<MeshRenderer>("meshrenderer");
	assert(mesh);
	mesh->setMeshName("Oil.mesh");
	mesh->setName("o" + std::to_string(gameManager()->getContPowerUps()));
	if (!mesh->createMesh())
		return nullptr;

	o = oil->addComponent<Oil>("oil");
	assert(o);
	o->setFriction(2);
	o->setOffset(3);
	o->setPosYOil(5.2);

	gameManager()->addPowerUp();

	return oil;
}

Entity* PowerUpObject::createNerfEntity()
{
	Entity* nerf = mEntity->getScene()->addEntity("Nerf" + std::to_string(gameManager()->getContPowerUps())).get();

	Transform* nerfTransfrom = nerf->addComponent<Transform>("transform");
	assert(nerfTransfrom);
	nerfTransfrom->setPosition(Vector3(0, -500, 0));
	nerfTransfrom->setScale(Vector3(1, 1, 1));
	
	AudioSource* nerfAudio = nerf->addComponent<AudioSource>("audiosource");
	assert(nerfAudio);
	nerfAudio->setSourceName("nerfSound" + std::to_string(gameManager()->getContPowerUps()));
	nerfAudio->setSourcePath("throwRocket.mp3");
	nerfAudio->setPlayOnStart(false);
	nerfAudio->setGroupChannelName("effects");
	nerfAudio->setVolume(4.0f);
	nerfAudio->setIsThreeD(true);
	nerfAudio->setLoop(false);
	nerfAudio->setMinDistance(1.0f);
	nerfAudio->setMaxDistance(60.0f);

	Collider* nerfCol = nerf->addComponent<Collider>("collider");
	assert(nerfCol);

	RigidBody* nerfRigidbody = nerf->addComponent<RigidBody>("rigidbody");
	assert(nerfRigidbody);
	nerfRigidbody->setColShape(SHAPES_BOX);
	nerfRigidbody->setMomeventType(MOVEMENT_TYPE_KINEMATIC);
	nerfRigidbody->setMass(1);
	nerfRigidbody->setGroup(2);
	nerfRigidbody->setMask(7);
	nerfRigidbody->setColliderScale(me::Vector3(1, .25, 1));
	nerfRigidbody->setTrigger(true);

	MeshRenderer* meshNerf = nerf->addComponent<MeshRenderer>("meshrenderer");
	assert(meshNerf);
	meshNerf->setMeshName("Nerf.mesh");
	meshNerf->setName("n" + std::to_string(gameManager()->getContPowerUps()));
	if (!meshNerf->createMesh())
		return nullptr;
	
	Nerf* nerfComp = nerf->addComponent<Nerf>("nerf");
	assert(nerfComp);
	nerfComp->setSpeed(30);

	gameManager()->addPowerUp();

	return nerf;
}
