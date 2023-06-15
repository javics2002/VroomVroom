#include "CameraFollow.h"
#include "EntityComponent/Transform.h"
#include "EntityComponent/Entity.h"
#include "MotorEngine/Scene.h"
#include "MotorEngine/SceneManager.h"
#include "Render/RenderManager.h"
#include "Render/RenderComponents/Camera.h"
#include "MotorEngine/MotorEngineError.h"

using namespace me;
using namespace VroomVroom;

Component* FactoryCameraFollow::create(Parameters& params)
{
	CameraFollow* camerafollow = new CameraFollow();
	camerafollow->setTargetName(Value(params, "target", std::string()));

	camerafollow->setPositionOffset(Vector3(Value(params, "positionoffset_x", 0.0f),
		Value(params, "positionoffset_y", 3.0f), Value(params, "positionoffset_z", 5.0f)));
	camerafollow->setLookOffset(Vector3(Value(params, "lookoffset_x", 0.0f),
		Value(params, "lookoffset_y", 3.0f), Value(params, "lookoffset_z", 5.0f)));

	camerafollow->setSmoothing(Value(params, "smoothing", 0.2f));
	return camerafollow;
}


void FactoryCameraFollow::destroy(me::Component* component)
{
	delete component;
}







CameraFollow::CameraFollow()
{
	mTargetTransform = nullptr;
	mCameraTransform = nullptr;
}

CameraFollow::~CameraFollow()
{
}

void CameraFollow::start()
{
	if (!sceneManager().getActiveScene()->findEntity(mTargetName)) {
		throwMotorEngineError("CameraFollow error", "Target entity was not found");
		sceneManager().quit();
	}
	mTargetTransform = sceneManager().getActiveScene()->findEntity(mTargetName).get()->getComponent<Transform>("transform");

	if (!mTargetTransform) {
		throwMotorEngineError("CameraFollow error", "Target entity doesn't have transform component");
		sceneManager().quit();
	}

	mCameraTransform = getEntity()->getComponent<Transform>("transform");

	if (!mCameraTransform) {
		throwMotorEngineError("CameraFollow error", "Camera entity doesn't have transform component");
		sceneManager().quit();
	}

	mCamera = getEntity()->getComponent<Camera>("camera");

	if (!mCamera) {
		throwMotorEngineError("CameraFollow error", "Camera entity doesn't have Camera component");
		sceneManager().quit();
	}

	renderManager().setCameraFixedY(mCamera->getName(), true);
}

void CameraFollow::lateUpdate(const double& dt)
{
	mCamera->setLookAt(mTargetTransform->getPosition() 
		+ mTargetTransform->right() * mLookOffset.x
		+ mTargetTransform->up() * mLookOffset.y
		+ mTargetTransform->forward() * mLookOffset.z);
	Vector3 newPosition = Vector3(mTargetTransform->getPosition() 
		+ mTargetTransform->right() * mPositionOffset.x
		+ mTargetTransform->up() * mPositionOffset.y
		+ mTargetTransform->forward() * mPositionOffset.z);
	
	Vector3 lerpedPosition = Vector3::Lerp(mCameraTransform->getPosition(), newPosition, mSmooth);
	mCameraTransform->setPosition(lerpedPosition);
}

void CameraFollow::setTargetName(std::string targetName)
{
	mTargetName = targetName;
}

void CameraFollow::setTarget(Transform* target)
{
	mTargetTransform = target;
}

void CameraFollow::setTarget(std::string targetName)
{
	mTargetTransform = sceneManager().getActiveScene()->findEntity(mTargetName).get()->getComponent<Transform>("transform");
}

void CameraFollow::setPositionOffset(Vector3 offset)
{
	mPositionOffset = offset;
}

void CameraFollow::setLookOffset(Vector3 offset)
{
	mLookOffset = offset;
}

void CameraFollow::setSmoothing(float smoothing)
{
	if (smoothing < 0)
		mSmooth = 0;
	else if (smoothing > 1)
		mSmooth = 1;
	else
		mSmooth = smoothing;
}
