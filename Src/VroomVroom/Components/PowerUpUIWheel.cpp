#include "PowerUpUIWheel.h"
#include "Utils/Timer.h"
#include "EntityComponent/Components/UISpriteRenderer.h"
#include "EntityComponent/Entity.h"
#include "EntityComponent/Scene.h"

using namespace me;
using namespace VroomVroom;

PowerUpUIWheel::PowerUpUIWheel()
{
}

PowerUpUIWheel::~PowerUpUIWheel()
{
	delete mSpriteIntervalTimer;
	delete mSpinTimer;
}

void PowerUpUIWheel::start() {
	mSpinning = false;
	mAnimEnd = false;
	mSpriteIntervalTimer = new Timer(false);
	mSpinTimer = new Timer(false);
	mTotalSpinTime = 1;
	mSpriteToLandOn = "NameNotSet";
	mLinkedUISprite = mEntity->getScene()->findEntity(mLinkedUISpriteName)->getComponent<UISpriteRenderer>("uispriterenderer");
}

void PowerUpUIWheel::update(const double& dt) {
	if (!mSpinning)
		return;

	mSpriteIntervalTimer->update(dt);
	mSpinTimer->update(dt);

	if (mSpriteIntervalTimer->getRawSeconds() > mSpinSpeed) {
		mSpriteIntervalTimer->reset();

		std::string lastName = mAvailableSpriteNames.front();
		mAvailableSpriteNames.pop_front();

		mLinkedUISprite->setSpriteMaterial(lastName);

		mAvailableSpriteNames.push_back(lastName);
	}

	if (mSpinTimer->getRawSeconds() > mTotalSpinTime) {
		mSpinTimer->reset();
		stopSpinOnSprite(mSpriteToLandOn);
	}
}

void PowerUpUIWheel::startSpinEffect() {
	mSpinning = true;
	mSpriteIntervalTimer->reset();
	mSpriteIntervalTimer->resume();
}


void PowerUpUIWheel::spinForSecondsAndLandOnSprite(float secs, std::string materialName) {
	startSpinEffect();
	mSpinTimer->reset();
	mSpinTimer->resume();
	mSpriteToLandOn = materialName;
	mTotalSpinTime = secs;
}

void PowerUpUIWheel::addSpriteNameToPool(std::string materialName) {
	mAvailableSpriteNames.push_back(materialName);
}

void VroomVroom::PowerUpUIWheel::setSpinSpeed(float spinSpeed)
{
	mSpinSpeed = spinSpeed;
}

void VroomVroom::PowerUpUIWheel::setLinked(std::string linkedUISpriteName)
{
	if (linkedUISpriteName != "")
		mLinkedUISpriteName = linkedUISpriteName;
}

void VroomVroom::PowerUpUIWheel::resetLinkSprite()
{
	mLinkedUISprite->resetSpriteMaterial();
	mAnimEnd = false;
}

bool VroomVroom::PowerUpUIWheel::isAnimEnd()
{
	return mAnimEnd;
}

void PowerUpUIWheel::stopSpinOnSprite(std::string materialName) {
	mSpinning = false;
	mAnimEnd = true;
	mSpriteIntervalTimer->pause();
	mLinkedUISprite->setSpriteMaterial(materialName);
	mAvailableSpriteNames.remove(materialName);
	mAvailableSpriteNames.push_front(materialName);
}
