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


	if (inputManager().getButton("LEFTCLICK" + std::to_string(0))) {
		Vector2 mousePosition = me::inputManager().getMousePositon();

		int w, h;
		w = window().getWindowWidth();
		h = window().getWindowHeight();

		if (mousePosition.x >= mUITransform->getPosition().x * w && 
			mousePosition.x <= mUITransform->getPosition().x * w + mUITransform->getScale().x * w  &&
			mousePosition.y >= mUITransform->getPosition().y * h && 
			mousePosition.y <= mUITransform->getPosition().y * h + mUITransform->getScale().y * h)
			execute();
	}
}

void UIButtonQuit::execute()
{
	sceneManager().quit();
}


