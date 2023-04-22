#include "CameraFollow.h"
#include "EntityComponent/Components/Transform.h"
#include "EntityComponent/Entity.h"
#include "EntityComponent/Scene.h"
#include "EntityComponent/SceneManager.h"
#include "Render/RenderManager.h"
#include "EntityComponent/Components/Camera.h"

me::CameraFollow::CameraFollow()
{
	mTargetTransform = nullptr;
	mCameraTransform = nullptr;
}

me::CameraFollow::~CameraFollow()
{
}

void me::CameraFollow::start()
{
	mTargetTransform = sceneManager().getActiveScene()->findEntity(mTargetName).get()->getComponent<Transform>("transform");
	mCameraTransform = getEntity()->getComponent<Transform>("transform");
	mCamera = getEntity()->getComponent<Camera>("camera");

	renderManager().setCameraFixedY(mCamera->getName(), true);
}

void me::CameraFollow::update()
{
	mCameraTransform->setPosition(mTargetTransform->getPosition() - mTargetTransform->forward() * 20); //Suavizar
	mCamera->setLookAt(mTargetTransform->getPosition());
	mCameraTransform->setPosition(mCameraTransform->getPosition() + Vector3(0, 5, 0));
}

void me::CameraFollow::setTargetName(std::string targetName)
{
	mTargetName = targetName;
}

void me::CameraFollow::setTarget(Transform* target)
{
	mTargetTransform = target;
}

void me::CameraFollow::setTarget(std::string targetName)
{
	mTargetTransform = sceneManager().getActiveScene()->findEntity(mTargetName).get()->getComponent<Transform>("transform");
}

void me::CameraFollow::setOffset(Vector3 offset)
{
	mOffset = offset;
}
