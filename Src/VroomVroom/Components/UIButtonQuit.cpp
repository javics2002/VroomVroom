#include "UIButtonQuit.h"
#include "Input/InputManager.h"
#include "Render/RenderManager.h"
#include "Audio/SoundManager.h"
#include "MotorEngine/SceneManager.h"
#include "GameManager.h"
#include "Render/UIComponents/UITransform.h"
#include "Audio/AudioComponents/AudioSource.h"
#include "EntityComponent/Entity.h"
#include "Render/Window.h"
#include "MotorEngine/MotorEngineError.h"

using namespace me;
using namespace VroomVroom;

me::Component* FactoryUIButtonQuit::create(me::Parameters& params)
{
	if (params.empty())
	{
		return new UIButtonQuit();
	}
	std::string sprite = Value(params, "sprite", std::string());
	std::string materialName = Value(params, "materialname", std::string());
	int zOrder = Value(params, "zorder", 1);

	UIButtonQuit* button = new UIButtonQuit();
	if (button->createSprite(sprite, materialName, zOrder)) {
		errorManager().throwMotorEngineError("Quit Button Factory Error", "A sprite with that name already exists.");
		delete button;
		return nullptr;
	}

	return button;
}

void FactoryUIButtonQuit::destroy(me::Component* component)
{
	delete component;
}


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
	if (!mButtonAudio) {
		errorManager().throwMotorEngineError("UIButtonQuit error", "An entity doesn't have AudioSource component");
		sceneManager().quit();
	}
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


