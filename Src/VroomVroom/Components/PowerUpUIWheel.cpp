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
}

void PowerUpUIWheel::init(float spinSpeed, std::string linkedUISpriteName) {
	mSpinSpeed = spinSpeed;

	if (linkedUISpriteName != "")
		mLinkedUISprite = getEntity()->getScene()->findEntity(linkedUISpriteName)->getComponent<UISpriteRenderer>("uispriterenderer");
}

void PowerUpUIWheel::start() {
	mSpinning = false;
	mSpriteIntervalTimer = new Timer(false);
	mSpinTimer = new Timer(false);
	mTotalSpinTime = 1;
	mSpriteToLandOn = "NameNotSet";
}

void PowerUpUIWheel::update(const double& dt) {
	if (!mSpinning)
		return;

	mSpriteIntervalTimer->update(dt);
	mSpinTimer->update(dt);

	if (mSpriteIntervalTimer->getRawSeconds() > 1.0 / mSpinSpeed) {
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

void PowerUpUIWheel::stopSpinOnSprite(std::string materialName) {
	mSpinning = false;
	mSpriteIntervalTimer->pause();
	mLinkedUISprite->setSpriteMaterial(materialName);
	mAvailableSpriteNames.remove(materialName);
	mAvailableSpriteNames.push_front(materialName);
}