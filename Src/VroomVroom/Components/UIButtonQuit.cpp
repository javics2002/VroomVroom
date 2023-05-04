#include "UIButtonQuit.h"
#include "Input/InputManager.h"
#include "Render/RenderManager.h"
#include "Audio/SoundManager.h"
#include "EntityComponent/SceneManager.h"
#include "GameManager.h"
#include "EntityComponent/Components/UITransform.h"
#include "EntityComponent/Components/AudioSource.h"
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

void VroomVroom::UIButtonQuit::start()
{
	UIButton::start();

	mButtonAudio = mEntity->getComponent<AudioSource>("audiosource");
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
		if (inputManager().getButton("LEFTCLICK")) {
			execute();
		}
		else if (stoppedSound) {
			toggleSound = true;
			stoppedSound = false;
			if(mButtonAudio != nullptr)
			mButtonAudio->play();
		}
	}
	else
		toggleSound = false;

	toggleHover();
}

void UIButtonQuit::execute()
{
	soundManager().stopEverySound();
	sceneManager().quit();
}

void VroomVroom::UIButtonQuit::toggleHover()
{
	if(!toggleSound && !stoppedSound)
	{
		stoppedSound = true;
	}
}


