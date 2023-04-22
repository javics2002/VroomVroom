#include "CameraFollow.h"
#include "EntityComponent/Components/Transform.h"
#include "EntityComponent/Entity.h"
#include "EntityComponent/Scene.h"
#include "EntityComponent/SceneManager.h"
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

void CameraFollow::update()
{
	mCameraTransform->setPosition(mTargetTransform->getPosition() - mTargetTransform->forward() * 20); //Suavizar
	mCamera->setLookAt(mTargetTransform->getPosition());
	mCameraTransform->setPosition(mCameraTransform->getPosition() + Vector3(0, 5, 0));
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

void CameraFollow::setOffset(Vector3 offset)
{
	mOffset = offset;
}
