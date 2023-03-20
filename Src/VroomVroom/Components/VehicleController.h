#pragma once
#ifndef __VROOMVROOM_VEHICLECONTROLLER
#define __VROOMVROOM_VEHICLECONTROLLER

#include "EntityComponent/Components/Component.h"

class VehicleController : public me::Component {
private:
    float mSpeed;
    float mRotationSpeed;
    float mDriftFactor;

public:
    VehicleController(float s, float rs, float df);

    void update();
};
#endif