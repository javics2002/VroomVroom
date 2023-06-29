#include "PowerUpObject.h"
#include "Oil.h"
#include "Nerf.h"
#include <math.h>
#include "VehicleController.h"
#include "Utils/Timer.h"
#include "EntityComponent/Entity.h"
#include "EntityComponent/Transform.h"
#include "Render/RenderComponents/MeshRenderer.h"
#include "Physics/PhysicsComponents/Rigidbody.h"
#include "Audio/AudioComponents/AudioSource.h"
#include "MotorEngine/Scene.h"
#include "GameManager.h"
#include "MotorEngine/SceneManager.h"
#include "MotorEngine/MotorEngineError.h"
#include "MotorEngine/InfoScene.h"

#include <iostream>
#include <cassert>

using namespace me;
using namespace VroomVroom;


me::Component* VroomVroom::FactoryPowerUpObject::create(me::Parameters& params)
{
	PowerUpObject* power = new PowerUpObject();
	power->setPower(PowerUpType(Value(params, "type", rand() % 3)));
	return power;
}

void VroomVroom::FactoryPowerUpObject::destroy(me::Component* component)
{
	delete component;
}

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
	if (!mTransform) {
		errorManager().throwMotorEngineError("PowerUpObject error", "PowerUpObject entity doesn't have transform component");
		sceneManager().quit();
        return;
	}
	mTakePowerAudio = mEntity->getComponent<AudioSource>("audiosource");
	if (!mTakePowerAudio) {
		errorManager().throwMotorEngineError("PowerUpObject error", "PowerUpObject entity doesn't have AudioSource component");
		sceneManager().quit();
        return;
	}
	mReviveTime = 4; // Set the time it takes for the power-up object to respawn after being picked up
	mPowerUpEntity = nullptr;
}

void PowerUpObject::update(const double& dt)
{
	if (mPicked) {
		mTimer->update(dt);
		if (mTimer->getRawSeconds() >= mReviveTime) {

			// Reactivate the MeshRenderer and RigidBody components of the power-up object after the respawn time has elapsed
			MeshRenderer* meshRenderer = mEntity->getComponent<MeshRenderer>("meshrenderer");
			if (!meshRenderer) {
				errorManager().throwMotorEngineError("PowerUpObject error", "PowerUpObject entity doesn't have MeshRenderer component");
				sceneManager().quit();
				return;
			}
			meshRenderer->activeMesh(); // Activamos de nuevo el componente MeshRenderer

			RigidBody* rigidBody = mEntity->getComponent<RigidBody>("rigidbody");
			if (!rigidBody) {
				errorManager().throwMotorEngineError("PowerUpObject error", "PowerUpObject entity doesn't have RigidBody component");
				sceneManager().quit();
				return;
			}
			rigidBody->activeBody();

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
		MeshRenderer* meshRenderer = mEntity->getComponent<MeshRenderer>("meshrenderer");
		if (!meshRenderer) {
			errorManager().throwMotorEngineError("PowerUpObject error", "PowerUpObject entity doesn't have MeshRenderer component");
			sceneManager().quit();
			return;
		}
		meshRenderer->desactiveMesh(); // Desactivamos el MeshRenderer para que no se vea por pantalla
		RigidBody* rigidBody = mEntity->getComponent<RigidBody>("rigidbody");
		if (!rigidBody) {
			errorManager().throwMotorEngineError("PowerUpObject error", "PowerUpObject entity doesn't have RigidBody component");
			sceneManager().quit();
			return;
		}
		rigidBody->desactiveBody(); // Desactivamos las colisiones
		mPicked = true;
		mTimer->resume();

		VehicleController* vehicleController = other->getComponent<VehicleController>("vehiclecontroller");
		if (!vehicleController) {
			errorManager().throwMotorEngineError("PowerUpObject error", 
				other->getName() + " entity doesn't have VehicleController component");
			sceneManager().quit();
			return;
		}
		
		if (!vehicleController->isPowerUpPicked()) {
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

			vehicleController->setPowerUp(mPowerUp, mPowerUpEntity);
			vehicleController->setPowerUpUI();
		}
	}
}

Entity* PowerUpObject::createOilEntity()
{
	if (gameManager() == nullptr) {
		errorManager().throwMotorEngineError("CreateOilEntity Error", "Game Manager does not exist");
		sceneManager().quit();
		return nullptr;
	}

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

	Parameters meshRendererParameters;
	meshRendererParameters["mesh"] = "o" + std::to_string(gameManager()->getContPowerUps());
	meshRendererParameters["meshname"] = "Oil.mesh";
	mesh = static_cast<MeshRenderer*>(oil->addComponent("meshrenderer", meshRendererParameters));
	if (!mesh)
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
	if (gameManager() == nullptr) {
		errorManager().throwMotorEngineError("CreateNerfEntity Error", "Game Manager does not exist");
		sceneManager().quit();
		return nullptr;
	}

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

	Parameters meshRendererParameters;
	meshRendererParameters["mesh"] = "n" + std::to_string(gameManager()->getContPowerUps());
	meshRendererParameters["meshname"] = "Nerf.mesh";
	MeshRenderer* meshNerf = static_cast<MeshRenderer*>(nerf->addComponent("meshrenderer", meshRendererParameters));
	if (!meshNerf)
		return nullptr;
	
	Nerf* nerfComp = nerf->addComponent<Nerf>("nerf");
	assert(nerfComp);
	nerfComp->setSpeed(30);

	gameManager()->addPowerUp();

	return nerf;
}
