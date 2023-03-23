#include "CameraFollow.h"
#include "EntityComponent/Components/Transform.h"
#include "EntityComponent/Entity.h"
#include "EntityComponent/Scene.h"
#include "EntityComponent/SceneManager.h"

me::CameraFollow::CameraFollow()
{
}

me::CameraFollow::~CameraFollow()
{
}

void me::CameraFollow::start()
{
	mTransform= getEntity()->getComponent<Transform>("transform");
}

void me::CameraFollow::update()
{
	//mTransform->setRotation(mTargetTransform->getRotation()); //Cambiar a look to
	mTransform->setPosition(mTargetTransform->getPosition()); //Suavizar
	mTransform->translate(mOffset);
	 
}

void me::CameraFollow::setTarget(Transform* target)
{
	mTargetTransform = target;
}

void me::CameraFollow::setTarget(std::string targetName)
{
	mTargetTransform = sceneManager().getActiveScene().get()->findEntity(targetName).get()->getComponent<Transform>("transform");
}

void me::CameraFollow::setOffset(Vector3 offset)
{
	mOffset = offset;
}
