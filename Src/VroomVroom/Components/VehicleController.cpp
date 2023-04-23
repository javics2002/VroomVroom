#include "VehicleController.h"
#include "Input/InputManager.h"
#include "EntityComponent/Entity.h"
#include "EntityComponent/Components/Transform.h"
#include "EntityComponent/Components/RigidBody.h"
#include "Checkpoint.h"
#include "Utils/Vector3.h"
#include "PowerUpObject.h"
#include <math.h>

using namespace me;
using namespace VroomVroom;

bool VehicleController::getPlayerButton(std::string buttonName)
{
    return inputManager().getButton(buttonName + std::to_string(mPlayerNumber));
}

float VehicleController::getPlayerAxis(std::string axisName)
{
    return inputManager().getAxis(axisName + std::to_string(mPlayerNumber));
}

VehicleController::VehicleController()
{
}

void VehicleController::start()
{
    mCheckpointIndex = 0;
    mLap = 0;
}

void VehicleController::update(const double& dt)
{
    // Get the input
    bool accelerate = getPlayerButton("ACCELERATE");
    bool decelerate = getPlayerButton("DECELERATE");
    bool drift = getPlayerButton("DRIFT");
    bool useObject = getPlayerButton("USEOBJECT");

    //If the player is using keyboard
    float deltaX = getPlayerAxis("HORIZONTAL");

    // Rotate the vehicle
    Vector3 direction = Vector3(0, 1, 0);

    if (deltaX < 0) { // Left
        mEntity->getComponent<RigidBody>("rigidbody")->addTorque(direction * (mRotationSpeed * deltaX));
    }
    if (deltaX > 0) { // Right
        mEntity->getComponent<RigidBody>("rigidbody")->addTorque(direction * (mRotationSpeed * deltaX));
    }

    Vector3 vForward = mEntity->getComponent<Transform>("transform")->forward();

    //std::cout << "rotated angle: " << rotatedV.x << " " << rotatedV.y << " " << rotatedV.z << "\n";

    if (accelerate) {
        // If the vertical input axis is positive, add a forward impulse to the vehicle's rigidbody
        mEntity->getComponent<RigidBody>("rigidbody")->addForce(vForward * mSpeed);
    }

    else if (decelerate) {
        // If the vertical input axis is negative, add a backward impulse to the vehicle's rigidbody
        mEntity->getComponent<RigidBody>("rigidbody")->addForce(vForward * -mSpeed);
    }

    //if (mPowerUp && useObject) {
    //    switch (mPowerUpType)
    //    {
    //    case NERF:
    //        // Create nerf entity  with nerf Component
    //        break;
    //    case OIL:
    //        //Create oil entity with Oil Component
    //        break;
    //    case THUNDER:
    //        // Create thunder entity  with thunder Component
    //        break;
    //    default:
    //        break;
    //    }

    //    mPowerUp = false;
    //}
}

void VehicleController::setSpeedAndDrift(float speed, float angularSpeed, float driftFactor)
{
    mSpeed = speed;
    mRotationSpeed = angularSpeed;
    mDriftFactor = driftFactor;
}

void VehicleController::setPowerUp(PowerUpType powerUpType)
{
    mPowerUpType = powerUpType;
    mPowerUp = true;
}

float VehicleController::getSpeed()
{
    return mSpeed;
}

void VehicleController::onCollisionEnter(me::Entity* other)
{
    if (other->hasComponent("Checkpoint")) {
        Checkpoint* checkpoint = other->getComponent<Checkpoint>("Checkpoint");

        if (checkpoint->getIndex() == (mCheckpointIndex + 1) % checkpoint->getNumCheckpoints()) {
            //Next checkpoint
            mCheckpointIndex++; 

            if (mCheckpointIndex == checkpoint->getNumCheckpoints()) {
                //Add lap
                mCheckpointIndex = 0;   
                mLap++;
            }
        }
        else if (checkpoint->getIndex() == (mCheckpointIndex + 1) % checkpoint->getNumCheckpoints())
        {
            //Previous checkpoint (you are in the wrong direction)
            mCheckpointIndex--; 

            if (mCheckpointIndex == -1) {
                //Remove lap
                mCheckpointIndex += checkpoint->getNumCheckpoints();
                mLap--;
            }
        }
    }

    //else if (other->hasComponent("PowerUpObject"))
}

void VehicleController::onCollisionExit(me::Entity* other)
{
    //TESTEAR SI ESTO HACE FALTA
    if (other->hasComponent("Checkpoint")) {
        Checkpoint* checkpoint = other->getComponent<Checkpoint>("Checkpoint");

        if (checkpoint->getIndex() == mCheckpointIndex + 1)
            mCheckpointIndex++;
        else if (checkpoint->getIndex() == mCheckpointIndex)
            mCheckpointIndex--; //Vas marcha atras por alguna razon
    }
}
