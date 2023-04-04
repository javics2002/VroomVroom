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

        //Index of the last valid checkpoint
        int checkpointIndex;


        bool mPowerUp;
        PowerUpType mPowerUpType;


    public:
        VehicleController();

        void start() override;
        void update() override;

        // Initializes the speed, rotation speed, and drift factor variables
        void setSpeedAndDrift(float speed, float angularSpeed, float driftFactor);

        void setPowerUp(PowerUpType powerUpType);

        /**
        Get the speed value of the Vehicle Controller component.
        @return A float object representing the speed.
        */
        float getSpeed();
        
        //void onCollisionEnter(Entity other) override {
        //    if (other.hascomponent<Checkpoint>("Checkpoint")) {
        //        if (checkpoint.index == checkpointIndex + 1)
        //            checkpointIndex++; 
        //        else if (checkpoint.index == checkpointIndex - 1)
        //            checkpointIndex--; //Vas marcha atras por alguna razon
        //    }
        //}

        //void onCollisionExit(Entity other) override {
        //    if (other.hascomponent<Checkpoint>("Checkpoint")) {
        //        if (checkpoint.index == checkpointIndex + 1)
        //            checkpointIndex++;
        //        else if (checkpoint.index == checkpointIndex)
        //            checkpointIndex--; //Vas marcha atras por alguna razon
        //    }
        //}
    };
}
#endif