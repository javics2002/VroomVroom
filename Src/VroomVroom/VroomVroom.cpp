#include "VroomVroom/VroomVroom.h"
#include "framework.h"
#include "EntityComponent/ComponentsFactory.h"
#include "VroomVroom/Components/Nerf.h"
#include "VroomVroom/Components/Oil.h"
#include "VroomVroom/Components/UIButtonScene.h"
#include "VroomVroom/Components/UIButtonQuit.h"
#include "VroomVroom/Components/PowerUpObject.h"
#include "VroomVroom/Components/PowerUpUiWheel.h"
#include "VroomVroom/Components/VehicleController.h"
#include "VroomVroom/Components/CircuitInfo.h"
#include "VroomVroom/Components/Checkpoint.h"
#include "VroomVroom/Components/CameraFollow.h"
#include "VroomVroom/Components/BoostPad.h"

#include "Components/GameManager.h"
#include "MotorEngine/SceneManager.h"
#include "EntityComponent/Entity.h"

// Input
#include "Input/InputManager.h"
#include "Input/InputCode.h"
#include "VroomVroom/VroomVroomInput.h"

using namespace me;
using namespace VroomVroom;

__VROOMVROOM_API const char* name()
{
	return "Vroom Vroom";
}

__VROOMVROOM_API bool init() {
	sceneManager().change("mainmenu.lua");
	return sceneManager().loadScene();
}

__VROOMVROOM_API void initFactories()
{
	componentsFactory().addFactoryComponent("camerafollow", new FactoryCameraFollow());
	componentsFactory().addFactoryComponent("vehiclecontroller", new FactoryVehicleController());
	componentsFactory().addFactoryComponent("circuitinfo", new FactoryCirtuitInfo());
	componentsFactory().addFactoryComponent("gamemanager", new FactoryGameManager());
	componentsFactory().addFactoryComponent("checkpoint", new FactoryCheckpoint());
	componentsFactory().addFactoryComponent("uibuttonscene", new FactoryUIButtonScene());
	componentsFactory().addFactoryComponent("uibuttonquit", new FactoryUIButtonQuit());
	componentsFactory().addFactoryComponent("powerupuiwheel", new FactoryPowerUpUIWheel());
	componentsFactory().addFactoryComponent("powerupobject", new FactoryPowerUpObject());
	componentsFactory().addFactoryComponent("oil", new FactoryOil());
	componentsFactory().addFactoryComponent("nerf", new FactoryNerf());
	componentsFactory().addFactoryComponent("boostpad", new FactoryBoostPad());
}

__VROOMVROOM_API void initInput()
{
	// --- Global input
	//Left click
	Input mouseClick;
	mouseClick.type = INPUTTYPE_MOUSE_CLICK;
	mouseClick.which = MOUSE_LEFTCLICK;
	inputManager().addButton("LEFTCLICK", mouseClick);

	//Return to main menu
	Input keyboardEscape, gamepadStart;
	keyboardEscape.type = INPUTTYPE_KEYBOARD;
	keyboardEscape.which = KEYBOARDCODE_ESCAPE;
	gamepadStart.type = INPUTTYPE_GAMEPAD_BUTTON;
	gamepadStart.which = GAMEPAD_BUTTONCODE_START;
	inputManager().addButton("CLOSE", keyboardEscape);
	inputManager().addBinding("CLOSE", gamepadStart);

	// --- Player input
	//Horizonal axis
	AxisInput keyboardHorizontal[PLAYERNUMBER_MAX];
	keyboardHorizontal[0].type = INPUTTYPE_KEYBOARD;
	keyboardHorizontal[0].positive = KEYBOARDCODE_D;
	keyboardHorizontal[0].negative = KEYBOARDCODE_A;

	keyboardHorizontal[1].type = INPUTTYPE_KEYBOARD;
	keyboardHorizontal[1].positive = KEYBOARDCODE_RIGHT; 
	keyboardHorizontal[1].negative = KEYBOARDCODE_LEFT;

	AxisInput gamepadLeftHorizontal;
	gamepadLeftHorizontal.type = INPUTTYPE_GAMEPAD_AXIS;
	gamepadLeftHorizontal.which = GAMEPAD_AXISCODE_LEFTX;

	AxisInput gamepadMotionHorizontal;
	gamepadMotionHorizontal.type = INPUTTYPE_GAMEPAD_AXIS;
	gamepadMotionHorizontal.which = GAMEPAD_AXISCODE_MOTION_ROLL;

	AxisInfo horizontalInfo;
	horizontalInfo.dead = .1f;
	horizontalInfo.gravity = .4f;
	inputManager().setMotionControlsSensitivity(0.0f, 0.0f, 0.0012f);

	//Accelerate
	Input keyboardAccelerate[PLAYERNUMBER_MAX];
	keyboardAccelerate[0].type = INPUTTYPE_KEYBOARD;
	keyboardAccelerate[0].which = KEYBOARDCODE_W;

	keyboardAccelerate[1].type = INPUTTYPE_KEYBOARD;
	keyboardAccelerate[1].which = KEYBOARDCODE_UP;

	Input gamepadA[PLAYERNUMBER_MAX];

	//Decelerate
	Input keyboardDecelerate[PLAYERNUMBER_MAX];
	keyboardDecelerate[0].type = INPUTTYPE_KEYBOARD;
	keyboardDecelerate[0].which = KEYBOARDCODE_S;

	keyboardDecelerate[1].type = INPUTTYPE_KEYBOARD;
	keyboardDecelerate[1].which = KEYBOARDCODE_DOWN;

	Input gamepadB[PLAYERNUMBER_MAX];

	//Use object
	Input keyboardUseObject[PLAYERNUMBER_MAX];
	keyboardUseObject[0].type = INPUTTYPE_KEYBOARD;
	keyboardUseObject[0].which = KEYBOARDCODE_SPACE;

	keyboardUseObject[1].type = INPUTTYPE_KEYBOARD;
	keyboardUseObject[1].which = KEYBOARDCODE_P;

	Input keyboardUseObjectAlt[PLAYERNUMBER_MAX];
	keyboardUseObjectAlt[0].type = INPUTTYPE_KEYBOARD;
	keyboardUseObjectAlt[0].which = KEYBOARDCODE_E;

	keyboardUseObjectAlt[1].type = INPUTTYPE_KEYBOARD;
	keyboardUseObjectAlt[1].which = KEYBOARDCODE_RCTRL;

	Input gamepadX[PLAYERNUMBER_MAX];
	Input gamepadY[PLAYERNUMBER_MAX];
	Input gamepadL[PLAYERNUMBER_MAX];
	Input gamepadR[PLAYERNUMBER_MAX];

	for (int playerI = PLAYERNUMBER_1; playerI != PLAYERNUMBER_MAX; playerI++) {
		//Create gamepad buttons
		gamepadB[playerI].type = INPUTTYPE_GAMEPAD_BUTTON;
		gamepadB[playerI].which = GAMEPAD_BUTTONCODE_B;
		gamepadA[playerI].type = INPUTTYPE_GAMEPAD_BUTTON;
		gamepadA[playerI].which = GAMEPAD_BUTTONCODE_A;
		gamepadX[playerI].type = INPUTTYPE_GAMEPAD_BUTTON;
		gamepadX[playerI].which = GAMEPAD_BUTTONCODE_X;
		gamepadY[playerI].type = INPUTTYPE_GAMEPAD_BUTTON;
		gamepadY[playerI].which = GAMEPAD_BUTTONCODE_Y;
		gamepadL[playerI].type = INPUTTYPE_GAMEPAD_BUTTON;
		gamepadL[playerI].which = GAMEPAD_BUTTONCODE_LEFT_SHOULDER;
		gamepadR[playerI].type = INPUTTYPE_GAMEPAD_BUTTON;
		gamepadR[playerI].which = GAMEPAD_BUTTONCODE_RIGHT_SHOULDER;

		//Horizontal movement axis with keyboard and controller
		inputManager().addAxis(playerButtonName("HORIZONTAL", playerI), horizontalInfo, keyboardHorizontal[playerI]);
		inputManager().addBinding(playerButtonName("HORIZONTAL", playerI), gamepadLeftHorizontal);
		inputManager().addBinding(playerButtonName("HORIZONTAL_MOTIONCONTROLS", playerI), gamepadMotionHorizontal);

		//Accelerate with keyboard and controller
		inputManager().addButton(playerButtonName("ACCELERATE", playerI), keyboardAccelerate[playerI], playerI);
		inputManager().addBinding(playerButtonName("ACCELERATE", playerI), gamepadA[playerI]);

		//Decelerate with keyboard and controller
		inputManager().addButton(playerButtonName("DECELERATE", playerI), keyboardDecelerate[playerI], playerI);
		inputManager().addBinding(playerButtonName("DECELERATE", playerI), gamepadB[playerI]);

		//Use object with keyboard and controller
		inputManager().addButton(playerButtonName("USEOBJECT", playerI), keyboardUseObject[playerI], playerI);
		inputManager().addBinding(playerButtonName("USEOBJECT", playerI), keyboardUseObjectAlt[playerI]);
		inputManager().addBinding(playerButtonName("USEOBJECT", playerI), gamepadX[playerI]);
		inputManager().addBinding(playerButtonName("USEOBJECT", playerI), gamepadY[playerI]);
		inputManager().addBinding(playerButtonName("USEOBJECT", playerI), gamepadL[playerI]);
		inputManager().addBinding(playerButtonName("USEOBJECT", playerI), gamepadR[playerI]);
	}
}