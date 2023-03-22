#pragma once
#ifndef __VROOMVROOM_VEHICLECONTROLLER
#define __VROOMVROOM_VEHICLECONTROLLER

#include "EntityComponent/Components/Component.h"
#include <string>

class VehicleController : public me::Component {
private:
    float mSpeed;
    float mRotationSpeed;
    float mDriftFactor;

    std::string mLeft;
    std::string mRight;
    std::string mDeltaX;
    std::string mAcelerate;
    std::string mDecelerate;
    std::string mDrift;

public:
    VehicleController(float s, float rs, float df);

    void update();

    void setInput(std::string left, std::string right, std::string deltaX,
        std::string acelerate, std::string decelerate, std::string drift);
};
#endif