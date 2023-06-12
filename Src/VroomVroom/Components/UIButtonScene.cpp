#include "UIButtonScene.h"
#include "Input/InputManager.h"
#include "Render/RenderManager.h"
#include "Audio/SoundManager.h"
#include "MotorEngine/SceneManager.h"
#include "GameManager.h"
#include "Render/UIComponents/UITransform.h"
#include "EntityComponent/Transform.h"
#include "Audio/AudioComponents/AudioSource.h"
#include "EntityComponent/Entity.h"
#include "Render/Window.h"
#include "MotorEngine/Scene.h"

using namespace me;
using namespace VroomVroom;

UIButtonScene::UIButtonScene()
{
}

UIButtonScene::~UIButtonScene()
{
	renderManager().destroyUISprite(mName);
}

void UIButtonScene::start()
{
	UIButton::start();

	windowWidth = window().getWindowWidth();
	windowHeight = window().getWindowHeight();

	mHoverAudio = mEntity->getComponent<AudioSource>("audiosource");


	if (!mPlayerLook.empty())
	{
		std::string delimiter = " ";
		std::string aux = mPlayerLook;

		int pos = 0;
		std::string token;

		while ((pos = aux.find(delimiter)) != std::string::npos)
		{
			token = aux.substr(0, pos);
			Transform* tr = sceneManager().getActiveScene()->findEntity(token).get()->getComponent<Transform>("transform");
			mPlayerLookTransform.push_back(tr);
			aux.erase(0, pos + delimiter.length());
		}
		Transform* tr = sceneManager().getActiveScene()->findEntity(aux).get()->getComponent<Transform>("transform");
		mPlayerLookTransform.push_back(tr);


	}

}


void UIButtonScene::setNewScene(std::string newScene) {
	mNewScene = newScene;
}

void UIButtonScene::setPlayerLook(std::string playerLook) {
	mPlayerLook = playerLook;
}


void UIButtonScene::update(const double& dt)
{
	/*if (!clickGot) {
		mClickAudio = mTransform->getChild(0)->getEntity()->getComponent<AudioSource>("audiosource");
		clickGot = true;
	}*/
	Vector2 mousePosition = me::inputManager().getMousePositon();
	windowWidth = window().getWindowWidth();
	windowHeight = window().getWindowHeight();

	if (mousePosition.x > mUITransform->getPosition().x * windowWidth &&
		mousePosition.x < mUITransform->getPosition().x * windowWidth + mUITransform->getScale().x * windowWidth &&
		mousePosition.y > mUITransform->getPosition().y * windowHeight &&
		mousePosition.y < mUITransform->getPosition().y * windowHeight + mUITransform->getScale().y * windowHeight) {
		if (inputManager().getButton("LEFTCLICK")) {
			//mClickAudio->play();
			execute();
			gameManager()->changeState(mNewScene);
		}
		else if (stoppedSound) {
			toggleSound = true;
			stoppedSound = false;
			if (mHoverAudio != nullptr)
			mHoverAudio->play();
		}
	}
	else
		toggleSound = false;

	if (!mPlayerLook.empty())
		togglePlayerLook(dt);
	else {
		toggleHover();
	}
}

void UIButtonScene::togglePlayerLook(const double& dt)
{
	if (toggleSound)
	{
		if (mPlayerLookTransform[0]->getScale().x <= 1.0)
		{
			for (Transform* tr : mPlayerLookTransform)
			{
				tr->setScale({ 2,2,2 });
			}

		}
		for (Transform* tr : mPlayerLookTransform)
		{
			tr->rotate(playerRotateAngle * dt, { 0,1,0 });
		}
	}
	else
	{
		if (!stoppedSound)
		{


			for (Transform* tr : mPlayerLookTransform)
			{
				tr->setRotation(Vector3{ 0,180,0 });
				tr->setScale({ 1,1,1 });

			}
			stoppedSound = true;
		}


	}
}
void VroomVroom::UIButtonScene::toggleHover()
{
	if (!toggleSound && !stoppedSound)
	{
		stoppedSound = true;
	}
}

void UIButtonScene::execute()
{
	soundManager().stopEverySound();

	std::list<std::string> awake;
	awake.push_back("createCheckpoints");

	sceneManager().change(mNewScene, awake);
}



