#pragma once
#ifndef __VROOMVROOM_VEHICLECONTROLLER
#define __VROOMVROOM_VEHICLECONTROLLER

#include "EntityComponent/Components/Component.h"
#include <string>

#include "PowerUpObject.h"

namespace me{


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

        //Index of the last valid checkpoint
        int checkpointIndex;


        bool mPowerUp;
        PowerUpType mPowerUpType;


    public:
        VehicleController();

        void start() override;
        void update() override;

        //set input info to vehicle controller
        void setInput(std::string left, std::string right, std::string deltaX,
            std::string acelerate, std::string decelerate, std::string drift, std::string useObject );

        // Initializes the speed, rotation speed, and drift factor variables
        void setSpeedAndDrift(float speed, float angularSpeed, float driftFactor);

        void setPowerUp(PowerUpType powerUpType);

        /**
        Get the speed value of the Vehicle Controller component.

        @return A float object representing the speed.
        */
        float getSpeed();

        //Esto va aqui?
        /*
        void OnCollisionEnter(Collider other) {
            if (other.hascomponent<Checkpoint>("Checkpoint")) {
                if (checkpoint.index == checkpointIndex + 1)
                    checkpointIndex++; 
                else if (checkpoint.index == checkpointIndex - 1)
                    checkpointIndex--; //Vas marcha atras por alguna razon
            }
        }

        void OnCollisionExit(Collider other) {
            if (other.hascomponent<Checkpoint>("Checkpoint")) {
                if (checkpoint.index == checkpointIndex + 1)
                    checkpointIndex++;
                else if (checkpoint.index == checkpointIndex)
                    checkpointIndex--; //Vas marcha atras por alguna razon
            }
        }*/
    };
}
#endif