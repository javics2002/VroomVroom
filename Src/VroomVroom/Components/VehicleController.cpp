#include "VehicleController.h"
#include "Input/InputManager.h"
#include "EntityComponent/Entity.h"
#include "EntityComponent/Components/Transform.h"
#include "EntityComponent/Components/RigidBody.h"
#include "Utils/Vector3.h"
#include "Input/InputCode.h"

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
    bool useObjeto = me::inputManager().getButton("USEOBJECT");

    //If the player is using keyboard
    bool left = me::inputManager().getButton("LEFT");
    bool right = me::inputManager().getButton("RIGHT");
    float deltaX = me::inputManager().getAxis("HORIZONTAL");


    // Rotate the vehicle if the player is using DualShock or Xbox controller
    if(deltaX != 0) {
        if (drift) {
            // If the vehicle is drifting, rotate it based on the drift factor
            mEntity->getComponent<me::Transform>("transform")->rotate( mRotationSpeed * deltaX * mDriftFactor, Vector3(0,1,0));
        }
        else {
            // Otherwise, rotate it normally
            mEntity->getComponent<me::Transform>("transform")->rotate(mRotationSpeed * deltaX, Vector3(0, 1, 0));
        }
    }
    //If the player is using keyboard
    else if(left)
        mEntity->getComponent<me::Transform>("transform")->rotate(-mRotationSpeed, Vector3(0, 1, 0));
    else if(right)
        mEntity->getComponent<me::Transform>("transform")->rotate(mRotationSpeed, Vector3(0, 1, 0));

    // Move the vehicle forward or backward
    me::Vector3 v;
    if (true) {
        // If the vertical input axis is positive, add a forward impulse to the vehicle's rigidbody
        //mEntity->getComponent<me::RigidBody>("rigidbody")->addImpulse(v.left()*mSpeed,mEntity->getComponent<me::Transform>("transform")->getPosition());
    }
    else if (decelerate) {
        // If the vertical input axis is negative, add a backward impulse to the vehicle's rigidbody
        //mEntity->getComponent<me::RigidBody>("transform")->addImpulse(v.forward()*-mSpeed,mEntity->getComponent<me::Transform>("transform")->getPosition());
    }


    if (mPowerUp && useObject) {
        switch (mPowerUpType)
        {
        case NERF:
            // Create nerf entity  with nerf Component
            break;
        case OIL:
            //Create oil entity with Oil Component
            break;
        case THUNDER:
            // Create thunder entity  with thunder Component
            break;
        default:
            break;
        }

        mPowerUp = false;
    }
}

void VehicleController::setInput(std::string left, std::string right, std::string deltaX, std::string acelerate, std::string decelerate, std::string drift, std::string useObject)
{
    mLeft = left;
    mRight = right;
    mDeltaX = deltaX;
    mAcelerate = acelerate;
    mDecelerate = decelerate;
    mDrift = drift;
    mUseObject = useObject;
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
