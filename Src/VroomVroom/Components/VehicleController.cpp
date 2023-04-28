//#include "VehicleController.h"
//
//#include "Input/InputManager.h"
//#include "EntityComponent/Entity.h"
//#include "EntityComponent/Scene.h"
//#include "EntityComponent/Components/Transform.h"
//#include "EntityComponent/Components/RigidBody.h"
//#include "Checkpoint.h"
//#include "CircuitInfo.h"
//#include "Utils/Vector3.h"
//#include "Utils/Vector4.h"
//#include "PowerUpObject.h"
//#include <math.h>
//#ifdef _DEBUG
//#include <iostream>
//#endif
//
//using namespace me;
//using namespace VroomVroom;
//
//bool VehicleController::getPlayerButton(std::string buttonName)
//{
//    return inputManager().getButton(buttonName + std::to_string(mPlayerNumber));
//}
//
//float VehicleController::getPlayerAxis(std::string axisName)
//{
//    return inputManager().getAxis(axisName + std::to_string(mPlayerNumber));
//}
//
//VehicleController::VehicleController()
//{
//    mCheckpointIndex = 0;
//    mCircuitInfo = nullptr;
//    mControllable = false;
//    mDriftFactor = 0;
//    mLap = 0;
//    mPlace = 0;
//    mPlayerNumber = PLAYERNUMBER_MAX;
//    mPowerUp = false;
//    mPowerUpType = PowerUpType::NERF;
//    mRigidBody = nullptr;
//    mRotationSpeed = 0;
//    mSpeed = 0;
//    mTransform = nullptr;
//}
//
//void VehicleController::start()
//{
//    mCheckpointIndex = 0;
//    mLap = 0;
//
//    mTransform = mEntity->getComponent<Transform>("transform");
//    mRigidBody = mEntity->getComponent<RigidBody>("rigidbody");
//    mCircuitInfo = mEntity->getScene()->findEntity("circuit").get()->getComponent<CircuitInfo>("circuitinfo");
//
//    mControllable = true;
//}
//
//void VehicleController::update(const double& dt)
//{
//    //Respawn if out of bounds
//    if (mTransform->getPosition().y <= mCircuitInfo->getDeathHeight())
//        mTransform->setPosition(mLastCheckpointPosition);
//
//    if (!mControllable)
//        return;
//
//    // Get the input
//    bool accelerate = getPlayerButton("ACCELERATE");
//    bool decelerate = getPlayerButton("DECELERATE");
//    bool drift = getPlayerButton("DRIFT");
//    bool useObject = getPlayerButton("USEOBJECT");
//
//    //If the player is using keyboard
//    float deltaX = getPlayerAxis("HORIZONTAL");
//
//    Vector3 vForward = mTransform->forward();
//
//    // If the vertical input axis is positive, add a forward impulse to the vehicle's rigidbody
//    if (accelerate)
//        mRigidBody->addForce(vForward * mSpeed * dt);
//
//    // If the vertical input axis is negative, add a backward impulse to the vehicle's rigidbody
//    else if (decelerate)
//        mRigidBody->addForce(vForward * -mSpeed * dt);
//
//    // Rotate the vehicle
//    float velocity = mRigidBody->getVelocity().magnitude(); //Coger velocity solo en vector forward.
//
//    mRigidBody->addForce(mTransform->right() * velocity * mRotationSpeed * deltaX * dt);
//
//    mTransform->rotate(deltaX * mDriftFactor * velocity, Vector3::up());
//
//    //if (mPowerUp && useObject) {
//    //    switch (mPowerUpType)
//    //    {
//    //    case NERF:
//    //        // Create nerf entity  with nerf Component
//    //        break;
//    //    case OIL:
//    //        //Create oil entity with Oil Component
//    //        break;
//    //    case THUNDER:
//    //        // Create thunder entity  with thunder Component
//    //        break;
//    //    default:
//    //        break;
//    //    }
//
//    //    mPowerUp = false;
//    //}
//}
//
//void VehicleController::setSpeedAndDrift(float speed, float angularSpeed, float driftFactor)
//{
//    mSpeed = speed;
//    mRotationSpeed = angularSpeed;
//    mDriftFactor = driftFactor;
//}
//
//void VehicleController::setPowerUp(PowerUpType powerUpType)
//{
//    mPowerUpType = powerUpType;
//    mPowerUp = true;
//}
//
//float VehicleController::getSpeed()
//{
//    return mSpeed;
//}
//
//void VehicleController::onCollisionEnter(me::Entity* other)
//{
//    if (other->hasComponent("Checkpoint")) {
//        Checkpoint* checkpoint = other->getComponent<Checkpoint>("Checkpoint");
//        mLastCheckpointPosition = checkpoint->getEntity()->getComponent<Transform>("transform")->getPosition();
//
//#ifdef _DEBUG
//        std::cout << "Car " << mPlayerNumber << " has reached checkpoint " << checkpoint->getIndex() << "\n";
//#endif
//
//        if (checkpoint->getIndex() == (mCheckpointIndex + 1) % checkpoint->getNumCheckpoints()) {
//            //Next checkpoint
//            mCheckpointIndex++; 
//
//            if (mCheckpointIndex == checkpoint->getNumCheckpoints()) {
//                //Add lap
//                mCheckpointIndex = 0;   
//                mLap++;
//
//#ifdef _DEBUG
//                std::cout << "Car " << mPlayerNumber << " started lap " << mLap << "\n";
//#endif
//
//                if (mLap == mCircuitInfo->getLaps()) {
//                    //Finish race
//                    mFinishTime = mCircuitInfo->getFinishTime();
//                    mControllable = false;
//
//#ifdef _DEBUG
//                    std::cout << "Car " << mPlayerNumber << " finished the race in " << mFinishTime << "\n";
//#endif
//                }
//            }
//        }
//        else if (checkpoint->getIndex() == (mCheckpointIndex + 1) % checkpoint->getNumCheckpoints())
//        {
//            //Previous checkpoint (you are in the wrong direction)
//            mCheckpointIndex--; 
//
//            if (mCheckpointIndex == -1) {
//                //Remove lap
//                mCheckpointIndex += checkpoint->getNumCheckpoints();
//                mLap--;
//            }
//        }
//    }
//
//    //else if (other->hasComponent("PowerUpObject"))
//}
//
//void VehicleController::onCollisionExit(me::Entity* other)
//{
//    //TESTEAR SI ESTO HACE FALTA
//    if (other->hasComponent("Checkpoint")) {
//        Checkpoint* checkpoint = other->getComponent<Checkpoint>("Checkpoint");
//
//        if (checkpoint->getIndex() == mCheckpointIndex + 1)
//            mCheckpointIndex++;
//        else if (checkpoint->getIndex() == mCheckpointIndex)
//            mCheckpointIndex--; //Vas marcha atras por alguna razon
//    }
//}

#include "VehicleController.h"
#include "GameManager.h"
#include "Input/InputManager.h"
#include "EntityComponent/Entity.h"
#include "EntityComponent/Scene.h"
#include "EntityComponent/Components/Transform.h"
#include "EntityComponent/Components/RigidBody.h"
#include "Checkpoint.h"
#include "CircuitInfo.h"
#include "PowerUpUIWheel.h"
#include "Utils/Vector3.h"
#include "Utils/Vector4.h"
#include "PowerUpObject.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "EntityComponent/SceneManager.h"
#ifdef _DEBUG
#include <iostream>
#endif

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
    mCheckpointIndex = 0;
    mCircuitInfo = nullptr;
    mControllable = false;
    mDriftFactor = 0;
    mLap = 0;
    mPlace = 0;
    mPlayerNumber = PLAYERNUMBER_MAX;
    mPowerUpType = PowerUpType::NERF;
    mRigidBody = nullptr;
    mRotationSpeed = 0;
    mSpeed = 0;
    mTransform = nullptr;
}

void VehicleController::start()
{
    mCheckpointIndex = -1;
    mLap = 0;

    mTransform = mEntity->getComponent<Transform>("transform");
    mRigidBody = mEntity->getComponent<RigidBody>("rigidbody");
    mPowerUpUIWheel = mEntity->getComponent<PowerUpUIWheel>("powerupuiwheel");

    mPowerUpUIWheel->addSpriteNameToPool("nerf");
    mPowerUpUIWheel->addSpriteNameToPool("oil");
    mPowerUpUIWheel->addSpriteNameToPool("lightningBolt");

    mCircuitInfo = mEntity->getScene()->findEntity("circuit").get()->getComponent<CircuitInfo>("circuitinfo");

    mControllable = true;
}

void VehicleController::update(const double& dt)
{
    //Respawn if out of bounds
    if (mTransform->getPosition().y <= mCircuitInfo->getDeathHeight())
        mTransform->setPosition(mLastCheckpointPosition);

    if (!mControllable)
        return;

    // Get the input
    bool accelerate = getPlayerButton("ACCELERATE");
    bool decelerate = getPlayerButton("DECELERATE");
    bool drift = getPlayerButton("DRIFT");
    bool useObject = getPlayerButton("USEOBJECT");

    //If the player is using keyboard
    float deltaX = getPlayerAxis("HORIZONTAL");

    Vector3 vForward = mTransform->forward();

    // If the vertical input axis is positive, add a forward impulse to the vehicle's rigidbody
    if (accelerate)
        mRigidBody->addForce(vForward * mSpeed * dt);

    // If the vertical input axis is negative, add a backward impulse to the vehicle's rigidbody
    else if (decelerate)
        mRigidBody->addForce(vForward * -mSpeed * dt);

    // Rotate the vehicle
    Vector3 velocity = mRigidBody->getVelocity(); //Coger velocity solo en vector forward.

    Vector3 forwardVector;

    Vector3 vector_radians = velocity;
    vector_radians.x = velocity.x * M_PI / 180.0;
    vector_radians.y = velocity.y * M_PI / 180.0;
    vector_radians.z = velocity.z * M_PI / 180.0;

    forwardVector.x = cos(vector_radians.y);
    forwardVector.y = -tan(vector_radians.x);
    forwardVector.z = -sin(vector_radians.y);

    mRigidBody->addForce(mTransform->right() * forwardVector.x * mRotationSpeed * deltaX * dt);

    mRigidBody->addTorque(Vector3::up() * (forwardVector.x * mDriftFactor * deltaX * dt));

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
    if (mPowerUpUIWheel->isAnimEnd() && useObject) {
        
        //me::Entity* powerUPEntity = new me::Entity();
        
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
            //mEntity->getComponent<RigidBody>("rigidbody")->addImpulse(rotatedV * mSpeed * 3);
            break;
        default:
            break;
        }

        mPowerUpUIWheel->resetLinkSprite();
    }
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

float VehicleController::getSpeed()
{
    return mSpeed;
}

void VehicleController::onCollisionEnter(me::Entity* other)
{
    if (other->hasComponent("checkpoint")) {
        Checkpoint* checkpoint = other->getComponent<Checkpoint>("checkpoint");
        mLastCheckpointPosition = checkpoint->getEntity()->getComponent<Transform>("transform")->getPosition();

#ifdef _DEBUG
        std::cout << "Car " << mPlayerNumber << " has reached checkpoint " << checkpoint->getIndex() << "\n";
#endif

        if (checkpoint->getIndex() == (mCheckpointIndex + 1) % checkpoint->getNumCheckpoints()) {
            //Next checkpoint
            mCheckpointIndex++;

            if (mCheckpointIndex == checkpoint->getNumCheckpoints()-1) {
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
    if (other->hasComponent("checkpoint")) {
        Checkpoint* checkpoint = other->getComponent<Checkpoint>("checkpoint");

        if (checkpoint->getIndex() == mCheckpointIndex + 1)
            mCheckpointIndex++;
        else if (checkpoint->getIndex() == mCheckpointIndex)
            mCheckpointIndex--; //Vas marcha atras por alguna razon
    }
}
