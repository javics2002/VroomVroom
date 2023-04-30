#include "VehicleController.h"

#include "Input/InputManager.h"
#include "EntityComponent/SceneManager.h"
#include "GameManager.h"

#include "EntityComponent/Entity.h"
#include "EntityComponent/Scene.h"
#include "EntityComponent/Components/Transform.h"
#include "EntityComponent/Components/RigidBody.h"

#include "Checkpoint.h"
#include "CircuitInfo.h"
#include "PowerUpUIWheel.h"
#include "PowerUpObject.h"

#include "Utils/Vector3.h"
#include "Utils/Vector4.h"
#include <iostream>
#include <math.h>

using namespace me;
using namespace VroomVroom;

VehicleController::VehicleController()
{
}

bool VehicleController::getPlayerButton(std::string buttonName)
{
    return inputManager().getButton(buttonName + std::to_string(mPlayerNumber));
}

float VehicleController::getPlayerAxis(std::string axisName)
{
    return inputManager().getAxis(axisName + std::to_string(mPlayerNumber));
}

void VehicleController::start()
{
    mTransform = mEntity->getComponent<Transform>("transform");
    mRigidBody = mEntity->getComponent<RigidBody>("rigidbody");
    mCircuitInfo = mEntity->getScene()->findEntity("circuit").get()->getComponent<CircuitInfo>("circuitinfo");

    mCheckpointIndex = 0;
    mLap = 0;
    mPlace = 0;
    mPlayerNumber = PLAYERNUMBER_1;

    mPowerUp = false;

    mControllable = true;
}

void VehicleController::update(const double& dt)
{
    //Respawn if out of bounds
    /*if (mTransform->getPosition().y <= mCircuitInfo->getDeathHeight())
        mTransform->setPosition(mLastCheckpointPosition);*/

    if (!mControllable)
        return;

    // Get the input
    bool accelerate = getPlayerButton("ACCELERATE");
    bool decelerate = getPlayerButton("DECELERATE");
    bool drift = getPlayerButton("DRIFT");
    bool useObject = getPlayerButton("USEOBJECT");

    //If the player is using keyboard
    float deltaX = getPlayerAxis("HORIZONTAL");

    Vector3 vForward = mTransform->forward().normalize();

    applyPush(dt, accelerate, decelerate);

    // Rotate the vehicle
    applyRotation(dt, deltaX);

    // make use of the power up active if it has anyone
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
            // Create thunder entity with thunder Component
            std::cout << "PowerUp used: " << "THUNDER" << std::endl;
            mEntity->getComponent<RigidBody>("rigidbody")->addImpulse(vForward * mAcceleration * 3);
            break;
        default:
            break;
        }

        mPowerUp = false;
    }
}

float VroomVroom::VehicleController::clampMax(float value, float max)
{
    if (value > max) return max;
    return value;
}

void VroomVroom::VehicleController::applyPush(const double& dt, bool accelerate, bool decelerate)
{
    if (accelerate) {
        Vector3 vForward = mTransform->forward().normalize();
        float velocity = mRigidBody->getVelocity().magnitude() + (mAcceleration * dt);

        // Limit velocity
        clampMax(velocity, maxSpeed);

        Vector3 newVelocity = vForward * velocity;

        mRigidBody->setVelocity(newVelocity);
    }
    else if (decelerate) {
        Vector3 vForward = mTransform->forward().normalize();
        float velocity = mRigidBody->getVelocity().magnitude() + (mAcceleration * dt);

        // Limit velocity
        // clampMax(velocity, maxSpeed);

        Vector3 newVelocity = vForward * -velocity;

        mRigidBody->setVelocity(newVelocity);
    }
    else {
        //Vector3 vForward = mTransform->forward().normalize();
        //Vector3 newForce = vForward * mRigidBody->getVelocity().magnitude();

        //mRigidBody->setVelocity(newForce);
    }

    
    // else if (decelerate)
}

void VroomVroom::VehicleController::applyRotation(const double& dt, float deltaX)
{
    if (deltaX != 0) {
        float rotationForce = mDriftFactor * mRotationSpeed;
        clampMax(rotationForce, maxAngularSpeed);

        Vector3 finalForce = Vector3::up() * rotationForce * deltaX * dt;

        mRigidBody->addTorque(finalForce);
    }
}



void VehicleController::setAccelerationAndRotation(float acceleration, float rotationSpeed, float driftFactor)
{
    mAcceleration = acceleration;
    mDeceleration = -acceleration / 2;
    mRotationSpeed = rotationSpeed;
    mDriftFactor = driftFactor;
}

void VehicleController::setPowerUp(PowerUpType powerUpType)
{
    mPowerUpType = powerUpType;
    mPowerUp = true;
}

void VroomVroom::VehicleController::setPowerUpUI()
{

    std::string name;

    switch (mPowerUpType)
    {
    case NERF:
        name = "nerf";
        break;
    case OIL:
        name = "oil";
        break;
    case THUNDER:
        name = "lightningBolt";
        break;
    }

    mPowerUpUIWheel->spinForSecondsAndLandOnSprite(3, name);
}

void VehicleController::setPlace(int newPlace)
{
    mPlace = newPlace;
}

int VehicleController::getPlace()
{
    return mPlace;
}

int VehicleController::getLap()
{
    return mLap;
}

int VehicleController::getChekpointIndex()
{
    return mCheckpointIndex;
}

void VehicleController::onCollisionEnter(me::Entity* other)
{
    if (other->hasComponent("checkpoint")) {
        Checkpoint* checkpoint = other->getComponent<Checkpoint>("checkpoint");
        mLastCheckpointPosition = checkpoint->getEntity()->getComponent<Transform>("transform")->getPosition();

#ifdef _DEBUG
        std::cout << "Car " << mPlayerNumber << " has reached checkpoint " << checkpoint->getIndex() << "\n";
#endif

        if (checkpoint->getIndex() == (mCheckpointIndex + 1) % checkpoint->GetNumCheckpoints()) {
            //Next checkpoint
            mCheckpointIndex++;

            if (mCheckpointIndex == checkpoint->GetNumCheckpoints() - 1) {
                //Add lap
                mCheckpointIndex = -1;
                mLap++;

#ifdef _DEBUG
                std::cout << "Car " << mPlayerNumber << " started lap " << mLap << "\n";
#endif

                if (mLap == mCircuitInfo->getLaps()) {
                    //Finish race
                    mFinishTime = mCircuitInfo->getFinishTime();
                    mControllable = false;

#ifdef _DEBUG
                    std::cout << "Car " << mPlayerNumber << " finished the race in " << mFinishTime << "\n";
#endif
                    sceneManager().change("results.lua");
                    gameManager()->changeState("results.lua");

                }
            }
        }
        else if (checkpoint->getIndex() == (mCheckpointIndex + 1) % checkpoint->GetNumCheckpoints())
        {
            //Previous checkpoint (you are in the wrong direction)
            mCheckpointIndex--;

            if (mCheckpointIndex == -1) {
                //Remove lap
                mCheckpointIndex += checkpoint->GetNumCheckpoints();
                mLap--;
            }
        }
    }

    //else if (other->hasComponent("PowerUpObject"))
}

void VehicleController::onCollisionExit(me::Entity* other)
{
    //TESTEAR SI ESTO HACE FALTA
    if (other->hasComponent("checkpoint")) {
        Checkpoint* checkpoint = other->getComponent<Checkpoint>("checkpoint");

        if (checkpoint->getIndex() == mCheckpointIndex + 1)
            mCheckpointIndex++;
        else if (checkpoint->getIndex() == mCheckpointIndex)
            mCheckpointIndex--; //Vas marcha atras por alguna razon
    }
}