#include "VroomVroomComponents.h"
#include "CameraFollow.h"
#include "VehicleController.h"

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
    VehicleController* vehicleController = new VehicleController(value(params, "speed", 0.0f),
        value(params, "rotationspeed", 0.0f), value(params, "driftfactor", 0.0f));

    return vehicleController;
}
