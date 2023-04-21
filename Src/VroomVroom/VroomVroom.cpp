#include "VroomVroom/VroomVroom.h"
#include "framework.h"
#include "EntityComponent/Components/ComponentsFactory.h"
#include "Components/VroomVroomComponents.h"
#include "Components/GameManager.h"
#include "EntityComponent/SceneManager.h"
#include "EntityComponent/Entity.h"

// Input
#include "Input/InputManager.h"
#include "Input/InputCode.h"
#include "VroomVroom/VroomVroomInput.h"

#define CREATE_PLAYER_BUTTON(buttonName) inputManager().addButton(playerButtonName(buttonName, playerI), playerI)

using namespace me;

__VROOMVROOM_API const char* name()
{
	return "Vroom Vroom";
}

__VROOMVROOM_API bool init() {
	/*sceneManager().addScene("Race");
	sceneManager().setActiveScene("Race");
	return sceneManager().loadEntities("race.lua") == 0;*/
	//sceneManager().addScene("GameManager");
	//sceneManager().setActiveScene("GameManager");
	if (sceneManager().addGameManager("gamemanager.lua") == 0) {
		sceneManager().getGameManager()->start();
		return true;
	}
	return false;

}

__VROOMVROOM_API void initFactories()
{
	componentsFactory().addFactoryComponent("camerafollow", new FactoryCameraFollow());
	componentsFactory().addFactoryComponent("vehiclecontroller", new FactoryVehicleController());
	componentsFactory().addFactoryComponent("wheelcontroller", new FactoryWheelController());
	componentsFactory().addFactoryComponent("circuitoinfo", new FactoryCirtuitoInfo());
	componentsFactory().addFactoryComponent("gamemanager", new FactoryGameManager());
	componentsFactory().addFactoryComponent("checkpoint", new FactoryCheckpoint());
	componentsFactory().addFactoryComponent("uibuttonscene", new FactoryUIButtonScene());
}

__VROOMVROOM_API void initInput()
{
	inputManager().addButton(playerButtonName("LEFTCLICK", 0), 0);

	Input mouseClick;
	mouseClick.type = INPUTTYPE_MOUSE_CLICK;
	mouseClick.which = MOUSE_LEFTCLICK;

	inputManager().addBinding(playerButtonName("LEFTCLICK", 0), mouseClick);

	for (int playerI = PLAYERNUMBER_1; playerI != PLAYERNUMBER_MAX; playerI++) {
		AxisInput horizontal;
		horizontal.type = INPUTTYPE_KEYBOARD;
		horizontal.positive = KEYBOARDCODE_A;
		horizontal.negative = KEYBOARDCODE_D;

		AxisInfo horizontalInfo;
		horizontalInfo.dead = .1f;
		horizontalInfo.gravity = .4f;

		inputManager().addAxis(playerButtonName("HORIZONTAL", playerI), horizontalInfo, horizontal);

		CREATE_PLAYER_BUTTON("ACCELERATE");
		CREATE_PLAYER_BUTTON("DECELERATE");
		CREATE_PLAYER_BUTTON("DRIFT");
		CREATE_PLAYER_BUTTON("USEOBJECT");
		

		Input keyboardS;
		keyboardS.type = INPUTTYPE_KEYBOARD;
		keyboardS.which = KEYBOARDCODE_S;

		inputManager().addBinding(playerButtonName("DECELERATE", playerI), keyboardS);

		Input keyboardW;
		keyboardW.type = INPUTTYPE_KEYBOARD;
		keyboardW.which = KEYBOARDCODE_W;

		inputManager().addBinding(playerButtonName("ACCELERATE", playerI), keyboardW);

		Input keyboardSpace;
		keyboardSpace.type = INPUTTYPE_KEYBOARD;
		keyboardSpace.which = KEYBOARDCODE_SPACE;

		inputManager().addBinding(playerButtonName("USEOBJECT", playerI), keyboardSpace);

		Input keyboardDrift;
		keyboardDrift.type = INPUTTYPE_KEYBOARD;
		keyboardDrift.which = KEYBOARDCODE_J;

		inputManager().addBinding(playerButtonName("DRIFT", playerI), keyboardDrift);
	}
}