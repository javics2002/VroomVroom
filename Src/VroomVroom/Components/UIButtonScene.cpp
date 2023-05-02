#include "UIButtonScene.h"
#include "Input/InputManager.h"
#include "Render/RenderManager.h"
#include "EntityComponent/SceneManager.h"
#include "GameManager.h"
#include "EntityComponent/Components/UITransform.h"
#include "EntityComponent/Components/Transform.h"
#include "EntityComponent/Entity.h"
#include "Render/Window.h"
#include "EntityComponent/Scene.h"

using namespace me;
using namespace VroomVroom;

UIButtonScene::UIButtonScene()
{
}

UIButtonScene::~UIButtonScene()
{
	renderManager().destroyUISprite(mName);
}

void UIButtonScene::init(std::string name, std::string materialName, int zOrder)
{
	mName = name;
	mSpriteName = materialName;

	if (mSpriteName.size() > 0)
	{
		renderManager().createSprite(mName, mSpriteName, zOrder);
	}

}

void UIButtonScene::start()
{
	UIButton::start();

	windowWidth = window().getWindowWidth();
	windowHeight = window().getWindowHeight();

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
	Vector2 mousePosition = me::inputManager().getMousePositon();
	windowWidth = window().getWindowWidth();
	windowHeight = window().getWindowHeight();

	if (mousePosition.x > mUITransform->getPosition().x * windowWidth &&
		mousePosition.x < mUITransform->getPosition().x * windowWidth + mUITransform->getScale().x * windowWidth &&
		mousePosition.y > mUITransform->getPosition().y * windowHeight &&
		mousePosition.y < mUITransform->getPosition().y * windowHeight + mUITransform->getScale().y * windowHeight) {
		if (inputManager().getButton("LEFTCLICK")) {
			execute();
			gameManager()->changeState(mNewScene);
		}
		else if (stopped) {
			toggle = true;
			stopped = false;
		}
	}
	else
		toggle = false;

	if (!mPlayerLook.empty())
		togglePlayerLook(dt);
}

void UIButtonScene::togglePlayerLook(const double& dt)
{
	if (toggle)
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
		if (!stopped)
		{


			for (Transform* tr : mPlayerLookTransform)
			{
				tr->setRotation(Vector3{ 0,180,0 });
				tr->setScale({ 1,1,1 });

			}
			stopped = true;
		}


	}
}
void UIButtonScene::execute()
{
	sceneManager().change(mNewScene);
}



