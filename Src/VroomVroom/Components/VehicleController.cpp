#include "VehicleController.h"
#include "Input/InputManager.h"
#include "EntityComponent/Entity.h"
#include "EntityComponent/Components/Transform.h"
#include "EntityComponent/Components/RigidBody.h"
#include "Utils/Vector3.h"

using namespace me;

VehicleController::VehicleController()
{
}

void me::VehicleController::start()
{
    checkpointIndex = 0;
}

/**
Returns the difference between this vector and another vector
@param v The other vector to subtract from this vector
@return The difference between this vector and the other vector
*/
void VehicleController::update()
{
    // Get the input
    bool acelerate = me::inputManager().getButton("ACELERATE");
    bool decelerate = me::inputManager().getButton("DECELERATE");
    bool drift = me::inputManager().getButton("DRIFT");
    bool useObject = me::inputManager().getButton("USEOBJECT");

    //If the player is using keyboard
    float deltaX = me::inputManager().getAxis("HORIZONTAL");

    // Rotate the vehicle
    if (deltaX < 0) { // Left
        mEntity->getComponent<me::Transform>("transform")->rotate(mRotationSpeed * deltaX, Vector3(0, 1, 0));
    }
    if (deltaX > 0) { // Right
        mEntity->getComponent<me::Transform>("transform")->rotate(mRotationSpeed * deltaX, Vector3(0, 1, 0));
    }

    // std::cout << deltaX << "\n";

    // Move the vehicle forward or backward
    Vector3 f;

    //me::Vector4 rotationQuat = mEntity->getComponent<me::Transform>("transform")->getRotation();
    //std::cout << "rot quat: " << rotationQuat.x << " " << rotationQuat.y << " " << rotationQuat.z << " " << rotationQuat.w << "\n";

    me::Vector3 rotationDegree = mEntity->getComponent<me::Transform>("transform")->getRotation().toEuler();
    std::cout << "rot degree euler: " << rotationDegree.x << " " << rotationDegree.y << " " << rotationDegree.z << "\n";

    rotationDegree.normalize();
    rotationDegree.dot(f.left());

    if (acelerate) {
        // If the vertical input axis is positive, add a forward impulse to the vehicle's rigidbody
        mEntity->getComponent<me::RigidBody>("rigidbody")->addForce(rotationDegree * mSpeed);
    }
    else if (decelerate) {
        // If the vertical input axis is negative, add a backward impulse to the vehicle's rigidbody
        mEntity->getComponent<me::RigidBody>("rigidbody")->addForce(rotationDegree * -mSpeed);
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

void me::VehicleController::setPowerUp(PowerUpType powerUpType)
{
    mPowerUpType = powerUpType;
    mPowerUp = true;
}

float VehicleController::getSpeed()
{
    return mSpeed;
}
