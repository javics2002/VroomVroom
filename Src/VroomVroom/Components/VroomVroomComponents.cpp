#include "VroomVroomComponents.h"
#include "CameraFollow.h"
#include "VehicleController.h"
#include "CircuitInfo.h"
#include "WheelController.h"
#include "GameManager.h"
#include "Checkpoint.h"
#include "Oil.h"
#include "UIButtonScene.h"
#include "UIButtonQuit.h"
#include "PowerUpUIWheel.h"
#include "PowerUpObject.h"

using namespace me;
using namespace VroomVroom;

Component* FactoryCameraFollow::create(Parameters& params)
{
    CameraFollow* camerafollow = new CameraFollow();
    camerafollow->setTargetName(Value(params, "target", std::string()));

    camerafollow->setPositionOffset(Vector3(Value(params, "positionoffset_x", 0.0f),
        Value(params, "positionoffset_y", 3.0f), Value(params, "positionoffset_z", 5.0f)));
    camerafollow->setLookOffset(Vector3(Value(params, "lookoffset_x", 0.0f),
        Value(params, "lookoffset_y", 3.0f), Value(params, "lookoffset_z", 5.0f)));
    
    camerafollow->setSmoothing(Value(params, "smoothing", 0.2f));
    return camerafollow;
}

void FactoryCameraFollow::destroy(me::Component* component)
{
    delete component;
}

Component* FactoryVehicleController::create(Parameters& params)
{
    VehicleController* vehicleController = new VehicleController();
    vehicleController->setSpeedAndDrift(Value(params, "speed", 0.0f),
        Value(params, "rotationspeed", 0.0f), Value(params, "driftfactor", 0.0f));
    vehicleController->setPlayerNumber(PlayerNumber(Value(params, "playernumber", 0)));
    
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

    checkpoint->setIndex(Value(params, "index", Checkpoint::GetNumCheckpoints()));

    return checkpoint;
}

void FactoryCheckpoint::destroy(Component* component)
{
    delete component;
}

Component* FactoryCirtuitInfo::create(Parameters& params)
{
    CircuitInfo* circuitInfo = new CircuitInfo();
    circuitInfo->setPosition(Vector3(Value(params, "position_x", 0.0f),
        Value(params, "position_y", 0.0f), Value(params, "position_z", 0.0f)));

    circuitInfo->setLaps(Value(params, "laps", 3));

    circuitInfo->setInfo(Value(params, "halfwidthinner", 36.0f), Value(params, "halfwidthouter", 44.0f), 
        Value(params, "halfheightinner", 1.7f), Value(params, "halfheightouter", 8.0f), 
        Value(params, "radiusinner", 1.7f), Value(params, "radiusouter", 8.0f));

    return circuitInfo;
}

void FactoryCirtuitInfo::destroy(Component* component)
{
    delete component;
}

Component* FactoryGameManager::create(Parameters& params)
{
    GameManager* gameManager = new GameManager();

    return gameManager;
}

void FactoryGameManager::destroy(Component* component)
{
    delete component;
}

Component* FactoryOil::create(Parameters& params)
{
    Oil* oil = new Oil();
    oil->setFriction(Value(params, "friction", 5.0f));
    return oil;

}

void FactoryOil::destroy(Component* component)
{
    delete component;
}

me::Component* FactoryUIButtonScene::create(me::Parameters& params)
{
    if (params.empty())
    {
        return new UIButtonScene();
    }
    std::string sprite = Value(params, "sprite", std::string());
    std::string materialName = Value(params, "materialname", std::string());
    std::string newScene = Value(params, "scene", std::string());
    std::string playerlook = Value(params, "playerlook", std::string());
    int zOrder= Value(params, "zorder", 1);

    UIButtonScene* button = new UIButtonScene();
    button->init(sprite, materialName,zOrder);
    button->setNewScene(newScene);
    button->setPlayerLook(playerlook);

    return button;
}

void FactoryUIButtonScene::destroy(me::Component* component)
{
    delete component;
}

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
    button->init(sprite, materialName, zOrder);



    return button;
}

void FactoryUIButtonQuit::destroy(me::Component* component)
{
    delete component;
}


me::Component* FactoryPowerUpUIWheel::create(me::Parameters& params)
{
    if (params.empty())
    {
        return new PowerUpUIWheel();
    }
    float spinSpeed = Value(params, "spinspeed", 0.2f);
    std::string linkedSpriteEntityName = Value(params, "linkedsprite", std::string());

    PowerUpUIWheel* powerUpWheel = new PowerUpUIWheel();
    powerUpWheel->setSpinSpeed(spinSpeed);
    powerUpWheel->setLinked(linkedSpriteEntityName);

    return powerUpWheel;
}

void FactoryPowerUpUIWheel::destroy(me::Component* component)
{
    delete component;
}

me::Component* VroomVroom::FactoryPowerUpObject::create(me::Parameters& params)
{
    PowerUpObject* power = new PowerUpObject();
    power->setPower(PowerUpType(Value(params, "type", rand() % 3)));
    return power;
}

void VroomVroom::FactoryPowerUpObject::destroy(me::Component* component)
{
    delete component;
}

me::Component* VroomVroom::FactoryNerf::create(me::Parameters& params)
{
    return nullptr;
}

void VroomVroom::FactoryNerf::destroy(me::Component* component)
{
    delete component;
}
