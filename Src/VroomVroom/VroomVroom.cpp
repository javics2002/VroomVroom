#include "VroomVroom/VroomVroom.h"
#include "framework.h"
#include "EntityComponent/Components/ComponentsFactory.h"
#include "Components/VroomVroomComponents.h"
#include "EntityComponent/SceneManager.h"

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