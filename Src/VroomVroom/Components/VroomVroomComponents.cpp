#include "VroomVroomComponents.h"
#include "CameraFollow.h"
#include "VehicleController.h"
#include "CircuitoInfo.h"
#include "WheelController.h"
#include "GameManager.h"
#include "Checkpoint.h"
#include "Oil.h"

using namespace me;

Component* FactoryCameraFollow::create(Parameters& params)
{
    CameraFollow* camerafollow = new CameraFollow();
    if (params.count("target"))
        camerafollow->setTarget(value(params, "target", std::string()));
    camerafollow->setOffset(Vector3(value(params, "offset_x", 0.0f),
        value(params, "offset_y", 3.0f), value(params, "offset_z", 5.0f)));
    //A�adir suavizado
    return camerafollow;
}

void FactoryCameraFollow::destroy(me::Component* component)
{
    delete component;
}

Component* FactoryVehicleController::create(Parameters& params)
{
    VehicleController* vehicleController = new VehicleController();
    vehicleController->setSpeedAndDrift(value(params, "speed", 0.0f),
        value(params, "rotationspeed", 0.0f), value(params, "driftfactor", 0.0f));
    
    return vehicleController;
}

void FactoryVehicleController::destroy(me::Component* component)
{
    delete component;
}

Component* FactoryWheelController::create(Parameters& params)
{
    WheelController* wheelController = new WheelController();

    return wheelController;
}

void FactoryWheelController::destroy(me::Component* component)
{
    delete component;
}

Component* FactoryCheckpoint::create(Parameters& params)
{
    Checkpoint* checkpoint = new Checkpoint();
    return checkpoint;
}

void FactoryCheckpoint::destroy(me::Component* component)
{
    delete component;
}

me::Component* FactoryCirtuitoInfo::create(me::Parameters& params)
{
    CircuitoInfo* circuitoInfo = new CircuitoInfo();
    circuitoInfo->setPosition(Vector3(value(params, "position_x", 0.0f),
        value(params, "position_y", 0.0f), value(params, "position_z", 0.0f)));
    return circuitoInfo;
}

void FactoryCirtuitoInfo::destroy(me::Component* component)
{
    delete component;
}

me::Component* FactoryGameManager::create(me::Parameters& params)
{
    return gameManager();
}

void FactoryGameManager::destroy(me::Component* component)
{
    delete component;
}

me::Component* FactoryOil::create(me::Parameters& params)
{
    Oil* oil = new Oil();
    oil->setFriction(value(params, "friction", 5.0f));
    return oil;

}

void FactoryOil::destroy(me::Component* component)
{
    delete component;
}
