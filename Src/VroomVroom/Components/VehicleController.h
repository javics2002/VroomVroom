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

    std::string mLeft;      //1:A   2: <-   //
    std::string mRight;     //1:D   2: ->   //
    std::string mDeltaX;    //1:Joystick    2:Joystick  //
    std::string mAcelerate;     //1:W   2:/\    //
    std::string mDecelerate;    //1:S   2:\/    //
    std::string mDrift;     
    std::string mUseObject; //1:Spacw   2:P     //

public:
    VehicleController(float s, float rs, float df);

    void update();

    //set input info to vehicle controller
    void setInput(std::string left, std::string right, std::string deltaX,
        std::string acelerate, std::string decelerate, std::string drift, std::string useObject );
};
#endif