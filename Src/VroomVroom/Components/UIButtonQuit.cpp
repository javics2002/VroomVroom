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


void UIButtonQuit::update(const double& dt)
{
	Vector2 mousePosition = me::inputManager().getMousePositon();
	windowWidth = window().getWindowWidth();
	windowHeight = window().getWindowHeight();

	if (mousePosition.x >= mUITransform->getPosition().x * windowWidth &&
		mousePosition.x <= mUITransform->getPosition().x * windowWidth + mUITransform->getScale().x * windowWidth &&
		mousePosition.y >= mUITransform->getPosition().y * windowHeight &&
		mousePosition.y <= mUITransform->getPosition().y * windowHeight + mUITransform->getScale().y * windowHeight){
		
		if (inputManager().getButton("LEFTCLICK" + std::to_string(0))) {
			execute();
		}
	}
}

void UIButtonQuit::execute()
{
	sceneManager().quit();
}


