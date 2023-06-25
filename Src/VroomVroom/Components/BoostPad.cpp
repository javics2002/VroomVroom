#include "BoostPad.h"

#include <math.h>
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
#include "VehicleController.h"

#include <iostream>
#include <cassert>

using namespace me;
using namespace VroomVroom;

me::Component* VroomVroom::FactoryBoostPad::create(me::Parameters& params)
{
	BoostPad* boostPad = new BoostPad();
	boostPad->setBoostMaxSpeedMultiplier(Value(params, "speedmultiplier", 2.0f));
	return boostPad;
}

void VroomVroom::FactoryBoostPad::destroy(me::Component* component)
{
	delete component;
}

VroomVroom::BoostPad::BoostPad()
{
}

VroomVroom::BoostPad::~BoostPad()
{
}

void VroomVroom::BoostPad::start()
{
	mTransform = mEntity->getComponent<Transform>("transform");
	if (!mTransform) {
		errorManager().throwMotorEngineError("BoostPad error", "BoostPad entity doesn't have transform component");
		sceneManager().quit();
		return;
	}

	mBoostAudio = mEntity->getComponent<AudioSource>("audiosource");
	if (!mBoostAudio) {
		errorManager().throwMotorEngineError("BoostPad error", "BoostPad entity doesn't have AudioSource component");
		sceneManager().quit();
		return;
	}
}

void VroomVroom::BoostPad::onCollisionEnter(me::Entity* other)
{
	if (other->hasComponent("vehiclecontroller")) {

		VehicleController* vehController = other->getComponent<VehicleController>("vehiclecontroller");
		if (!vehController) {
			errorManager().throwMotorEngineError("BoostPad error",
				other->getName() + " entity doesn't have VehicleController component");
			sceneManager().quit();
			return;
		}

		mBoostAudio->play();

		vehController->setMaxSpeedAndRotationSpeed(vehController->getOrigMaxSpeed() * mBoostMaxSpeedMultiplier, vehController->getMaxAngularSpeed());
		RigidBody* rigidbody = other->getComponent<RigidBody>("rigidbody");
		if (!rigidbody) {
			errorManager().throwMotorEngineError("VehicleController error",
				mEntity->getName() + " entity doesn't have RigidBody component");
			sceneManager().quit();
			return;
		}
		Transform* tr = other->getComponent<Transform>("transform");
		if (!tr) {
			errorManager().throwMotorEngineError("VehicleController error",
				mEntity->getName() + " entity doesn't have Transform component");
			sceneManager().quit();
			return;
		}
		rigidbody->addImpulse(tr->forward().normalize() * vehController->getBoostImpulse());
		vehController->resetSpeedBoostTimer();
		vehController->resumeSpeedBoostTimer();
	}

}

void VroomVroom::BoostPad::setBoostMaxSpeedMultiplier(float maxSpeedMult)
{
	mBoostMaxSpeedMultiplier = maxSpeedMult;
}
