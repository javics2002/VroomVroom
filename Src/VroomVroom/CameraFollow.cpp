#include "CameraFollow.h"
#include "EntityComponent/Transform.h"
#include "EntityComponent/Entity.h"

me::CameraFollow::CameraFollow(Transform* player)
{
	mPlayerTr = player;
}

me::CameraFollow::~CameraFollow()
{
}

void me::CameraFollow::start()
{
	mTransform= getEntity()->getComponent<Transform>("transform");
	mOffset = mTransform->getPosition()- mPlayerTr->getPosition();
}

void me::CameraFollow::update()
{
	mTransform->setRotation(mPlayerTr->getRotation());
	mTransform->setPosition(mPlayerTr->getPosition());
	mTransform->translate(mOffset);
	 
}
