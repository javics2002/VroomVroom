#pragma once
#ifndef __VROOMVROOM_VEHICLECONTROLLER
#define __VROOMVROOM_VEHICLECONTROLLER

#include "EntityComponent/Components/Component.h"
#include <string>

namespace me{
    class VehicleController : public me::Component {
    private:
        float mSpeed;
        float mRotationSpeed;
        float mDriftFactor;

        //Index of the last valid checkpoint
        int checkpointIndex;

    public:
        VehicleController();

        void start() override;
        void update() override;

        // Initializes the speed, rotation speed, and drift factor variables
        void setSpeedAndDrift(float speed, float angularSpeed, float driftFactor);

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