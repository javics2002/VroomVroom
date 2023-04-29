#include "UIButtonQuit.h"
#include "Input/InputManager.h"
#include "Render/RenderManager.h"
#include "EntityComponent/SceneManager.h"
#include "GameManager.h"
#include "EntityComponent/Components/UITransform.h"
#include "EntityComponent/Entity.h"
#include "Render/Window.h"

using namespace me;
using namespace VroomVroom;

UIButtonQuit::UIButtonQuit()
{
}

UIButtonQuit::~UIButtonQuit()
{
	renderManager().destroyUISprite(mName);
}

void UIButtonQuit::init(std::string name, std::string materialName,int zOrder)
{
	mName = name;
	mSpriteName = materialName;

	if (mSpriteName.size() > 0)
	{
		renderManager().createSprite(mName, mSpriteName,zOrder);
	}

}

void UIButtonQuit::start()
{
	mUITransform = getEntity()->getComponent<UITransform>("uitransform");
	renderManager().setUISpriteTransform(mName, mUITransform->getPosition(), mUITransform->getScale(), mUITransform->getRotation());
}


void UIButtonQuit::update(const double& dt)
{
	if (inputManager().getButton("LEFTCLICK" + std::to_string(0))) {
		Vector2 mousePosition = me::inputManager().getMousePositon();
		std::cout << mousePosition.x << " + " << mousePosition.y << "\n";

		int w, h;
		w = window().getWindowWidth();
		h = window().getWindowHeight();
		std::cout << mUITransform->getPosition().x * w << " + " << mUITransform->getPosition().y * h  << "\n";

		if (mousePosition.x >= mUITransform->getPosition().x * w && mousePosition.x <= mUITransform->getPosition().y * w + mUITransform->getScale().x * w  &&
			mousePosition.y >= mUITransform->getPosition().y * h && mousePosition.y <= mUITransform->getPosition().y * h + mUITransform->getScale().y * h) {
			execute();
			

		}
	}
}

void UIButtonQuit::execute()
{
	sceneManager().quit();
}

std::string UIButtonQuit::getName()
{
	return mName;
}

void UIButtonQuit::setSpriteMaterial(std::string materialName)
{
	renderManager().setUISpriteMaterial(mName, materialName);
}


