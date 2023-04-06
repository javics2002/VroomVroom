#include "VehicleController.h"
#include "Input/InputManager.h"
#include "EntityComponent/Entity.h"
#include "EntityComponent/Components/Transform.h"
#include "EntityComponent/Components/RigidBody.h"
#include "Utils/Vector3.h"
#include "PowerUpObject.h"
#include <math.h>

using namespace me;

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
}

void VehicleController::update()
{
    // Get the input
    bool accelerate = getPlayerButton("ACCELERATE");
    bool decelerate = getPlayerButton("DECELERATE");
    bool drift = getPlayerButton("DRIFT");
    bool useObject = getPlayerButton("USEOBJECT");

    //If the player is using keyboard
    float deltaX = getPlayerAxis("HORIZONTAL");

    // Rotate the vehicle
    if (deltaX < 0) { // Left
        mEntity->getComponent<Transform>("transform")->rotate(mRotationSpeed * deltaX, Vector3(0, 1, 0));
    }
    if (deltaX > 0) { // Right
        mEntity->getComponent<Transform>("transform")->rotate(mRotationSpeed * deltaX, Vector3(0, 1, 0));
    }

    Vector3 rot = mEntity->getComponent<Transform>("transform")->getRotation().toEuler(); // reemplazar con el cuaterni�n a utilizar
    Vector3 v; // reemplazar con el vector3 a rotar

    Vector3 rotatedV;

    Vector3 vector_radians = rot;
    vector_radians.x = rot.x * 3.1415926 / 180.0;
    vector_radians.y = rot.y * 3.1415926 / 180.0;
    vector_radians.z = rot.z * 3.1415926 / 180.0;
    
    rotatedV.x = cos(vector_radians.y);
    rotatedV.y = -tan(vector_radians.x);
    rotatedV.z = -sin(vector_radians.y);

    if (std::abs(rotatedV.x) < 0.000001) {
        rotatedV.x = 0;
    }

    if (std::abs(rotatedV.y) < 0.000001) {
        rotatedV.y = 0;
    }

    if (std::abs(rotatedV.z) < 0.000001) {
        rotatedV.z = 0;
    }


    rotatedV.dot(v.left());

    //std::cout << "rotated angle: " << rotatedV.x << " " << rotatedV.y << " " << rotatedV.z << "\n";

    if (accelerate ) {
        // If the vertical input axis is positive, add a forward impulse to the vehicle's rigidbody
        mEntity->getComponent<RigidBody>("rigidbody")->addForce(rotatedV * mSpeed);
    }

    else if (decelerate) {
        // If the vertical input axis is negative, add a backward impulse to the vehicle's rigidbody
        mEntity->getComponent<RigidBody>("rigidbody")->addForce(rotatedV * -mSpeed);
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
