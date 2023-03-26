#include "VroomVroomComponents.h"
#include "CameraFollow.h"
#include "VehicleController.h"
#include "CircuitoInfo.h"
#include "GameManager.h"
#include "Checkpoint.h"

using namespace me;

Component* FactoryCameraFollow::create(Parameters params)
{
    CameraFollow* camerafollow = new CameraFollow();
    if (params.count("target"))
        camerafollow->setTarget(value(params, "target", std::string()));
    camerafollow->setOffset(Vector3(value(params, "offset_x", 0.0f),
        value(params, "offset_y", 3.0f), value(params, "offset_z", 5.0f)));
    //Añadir suavizado
    return camerafollow;
}

Component* FactoryVehicleController::create(Parameters params)
{
    //Constructor vacio!!
    VehicleController* vehicleController = new VehicleController(value(params, "speed", 0.0f),
        value(params, "rotationspeed", 0.0f), value(params, "driftfactor", 0.0f));

    return vehicleController;
}

Component* FactoryCheckpoint::create(Parameters params)
{
    Checkpoint* checkpoint = new Checkpoint();
    return checkpoint;
}

me::Component* FactoryCirtuitoInfo::create(me::Parameters params)
{
    CircuitoInfo* circuitoInfo = new CircuitoInfo();
    circuitoInfo->setPosition(Vector3(value(params, "position_x", 0.0f),
        value(params, "position_y", 0.0f), value(params, "position_z", 0.0f)));
    return circuitoInfo;
}

me::Component* FactoryGameManager::create(me::Parameters params)
{
    return gameManager();
    
}
