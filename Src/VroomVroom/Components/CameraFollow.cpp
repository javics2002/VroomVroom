#include "CameraFollow.h"
#include "EntityComponent/Components/Transform.h"
#include "EntityComponent/Entity.h"
#include "MotorEngine/Scene.h"
#include "MotorEngine/SceneManager.h"
#include "Render/RenderManager.h"
#include "EntityComponent/Components/Camera.h"

using namespace me;
using namespace VroomVroom;

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
	mTargetTransform = sceneManager().getActiveScene()->findEntity(mTargetName).get()->getComponent<Transform>("transform");
	mCameraTransform = getEntity()->getComponent<Transform>("transform");
	mCamera = getEntity()->getComponent<Camera>("camera");

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
