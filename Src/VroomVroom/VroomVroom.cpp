#include "VroomVroom/VroomVroom.h"
#include "framework.h"
#include "EntityComponent/Components/ComponentsFactory.h"
#include "Components/VroomVroomComponents.h"
#include "EntityComponent/SceneManager.h"

// Input
#include "Input/InputManager.h"
#include "Input/InputCode.h"

using namespace me;

__VROOMVROOM_API const char* name()
{
	return "Vroom Vroom";
}

__VROOMVROOM_API bool init() {
	sceneManager().addScene("Race");
	sceneManager().setActiveScene("Race");
	return sceneManager().loadEntities("race.lua") == 0;
}

__VROOMVROOM_API void initFactories()
{
	componentsFactory().addFactoryComponent("camerafollow", new FactoryCameraFollow());
	componentsFactory().addFactoryComponent("vehiclecontroller", new FactoryVehicleController());
	componentsFactory().addFactoryComponent("wheelcontroller", new FactoryWheelController());
	componentsFactory().addFactoryComponent("circuitoinfo", new FactoryCirtuitoInfo());
	componentsFactory().addFactoryComponent("gamemanager", new FactoryGameManager());
	componentsFactory().addFactoryComponent("checkpoint", new FactoryCheckpoint());
}


__VROOMVROOM_API void initInput()
{
	AxisInput horizontal;
	horizontal.type = INPUTTYPE_KEYBOARD;
	horizontal.positive = KEYBOARDCODE_A;
	horizontal.negative = KEYBOARDCODE_D;

	AxisInfo horizontalInfo;
	horizontalInfo.dead = .1f;
	horizontalInfo.gravity = .4f;

	inputManager().addAxis("HORIZONTAL", horizontalInfo, horizontal);

	inputManager().addButton("ACELERATE");
	inputManager().addButton("DECELERATE");
	inputManager().addButton("DRIFT");
	inputManager().addButton("USEOBJECT");

	Input keyboardS;
	keyboardS.type = INPUTTYPE_KEYBOARD;
	keyboardS.which = KEYBOARDCODE_S;

	inputManager().addBinding("DECELERATE", keyboardS);

	Input keyboardW;
	keyboardW.type = INPUTTYPE_KEYBOARD;
	keyboardW.which = KEYBOARDCODE_W;

	inputManager().addBinding("ACELERATE", keyboardW);

	Input keyboardSpace;
	keyboardSpace.type = INPUTTYPE_KEYBOARD;
	keyboardSpace.which = KEYBOARDCODE_SPACE;

	inputManager().addBinding("USEOBJECT", keyboardSpace);

	Input keyboardDrift;
	keyboardDrift.type = INPUTTYPE_KEYBOARD;
	keyboardDrift.which = KEYBOARDCODE_J;

	inputManager().addBinding("DRIFT", keyboardDrift);
}