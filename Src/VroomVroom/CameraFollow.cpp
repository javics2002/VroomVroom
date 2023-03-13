#include "CameraFollow.h"

me::CameraFollow::CameraFollow(Transform* player)
{
	mPlayer = player;
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
	mTransfor->setRotation(mPlayerTr->getRotation);
	mTransform->setPosition(mPlayerTr->getPosition());
	mTransform->translate(offsetof);
	 
}
