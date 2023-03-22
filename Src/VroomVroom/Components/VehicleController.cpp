#include "VehicleController.h"
#include "Input/InputManager.h"
#include "EntityComponent/Entity.h"
#include "EntityComponent/Components/Transform.h"
#include "EntityComponent/Components/RigidBody.h"
#include "EntityComponent/Entity.h"
#include "Utils/Vector3.h"

using namespace me;

VehicleController::VehicleController(float s, float rs, float df)
{
    // Constructor - Initializes the speed, rotation speed, and drift factor variables
    mSpeed = s;
    mRotationSpeed = rs;
    mDriftFactor = df;
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

    //If the player is using keyboard
    bool left = me::inputManager().getButton("LEFT");
    bool right = me::inputManager().getButton("RIGHT");
    float deltaX = me::inputManager().getAxis("HORIZONTAL");

    /*
    // Get the input
    bool acelerate = me::inputManager().getButton(mAcelerate);
    bool decelerate = me::inputManager().getButton(mDecelerate);
    bool drift = me::inputManager().getButton(mDrift);

    //If the player is using keyboard
    bool left = me::inputManager().getButton(mLeft);
    bool right = me::inputManager().getButton(mRight);
    float deltaX = me::inputManager().getAxis(mDeltaX);
    */


    // Rotate the vehicle if the player is using DualShock or Xbox controller
    if(deltaX != 0) {
        if (drift) {
            // If the vehicle is drifting, rotate it based on the drift factor
            mEntity->getComponent<me::Transform>("transform")->rotate( mRotationSpeed * deltaX * mDriftFactor, me::AXIS_ROTATIONS_Y);
        }
        else {
            // Otherwise, rotate it normally
            mEntity->getComponent<me::Transform>("transform")->rotate(mRotationSpeed * deltaX, me::AXIS_ROTATIONS_Y);
        }
    }
    //If the player is using keyboard
    else if(left)
        mEntity->getComponent<me::Transform>("transform")->rotate(-mRotationSpeed, me::AXIS_ROTATIONS_Y);
    else if(right)
        mEntity->getComponent<me::Transform>("transform")->rotate(mRotationSpeed, me::AXIS_ROTATIONS_Y);

    // Move the vehicle forward or backward
    me::Vector3 v;
    if (acelerate) {
        // If the vertical input axis is positive, add a forward impulse to the vehicle's rigidbody
        mEntity->getComponent<me::RigidBody>("transform")->addImpulse(v.forward()*mSpeed,mEntity->getComponent<me::Transform>("transform")->getPosition());
    }
    else if (decelerate) {
        // If the vertical input axis is negative, add a backward impulse to the vehicle's rigidbody
        mEntity->getComponent<me::RigidBody>("transform")->addImpulse(v.forward()*-mSpeed,mEntity->getComponent<me::Transform>("transform")->getPosition());
    }
}

void VehicleController::setInput(std::string left, std::string right, std::string deltaX, std::string acelerate, std::string decelerate, std::string drift)
{
    mLeft = left;
    mRight = right;
    mDeltaX = deltaX;
    mAcelerate = acelerate;
    mDecelerate = decelerate;
    mDrift = drift;
}
