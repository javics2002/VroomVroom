#include "VehicleController.h"

#include "Input/InputManager.h"
#include "EntityComponent/Entity.h"
#include "EntityComponent/Scene.h"
#include "EntityComponent/Components/Transform.h"
#include "EntityComponent/Components/RigidBody.h"
#include "Checkpoint.h"
#include "CircuitInfo.h"
#include "Utils/Vector3.h"
#include "Utils/Vector4.h"
#include "PowerUpObject.h"
#include <math.h>
#ifdef _DEBUG
#include <iostream>
#endif
#define MY_PI 3.14159265358979323846

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
    mPowerUp = false;
    mPowerUpType = PowerUpType::NERF;
    mRigidBody = nullptr;
    mRotationSpeed = 0;
    mSpeed = Vector2();
    mTransform = nullptr;
}

void VehicleController::start()
{
    mCheckpointIndex = 0;
    mLap = 0;

    mTransform = mEntity->getComponent<Transform>("transform");
    mRigidBody = mEntity->getComponent<RigidBody>("rigidbody");
    mCircuitInfo = mEntity->getScene()->findEntity("circuit").get()->getComponent<CircuitInfo>("circuitinfo");

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

    // If the vertical input axis is positive, add a forward impulse to the vehicle's rigidbody
    if (accelerate)
        mRigidBody->addForce(vForward * mAcceleration * dt);

    // If the vertical input axis is negative, add a backward impulse to the vehicle's rigidbody
    else if (decelerate)
        mRigidBody->addForce(vForward * mDeceleration * dt);

    // Rotate the vehicle
    if (deltaX != 0)
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

void VehicleController::fixedUpdate() {
    // Actualizar la velocidad y la dirección del coche
    float increase = mAcceleration - mFriction;
    mVelocity = mVelocity + increase;
    mDirection += mRotation;

    // Aplicar la gravedad para simular la caída del coche
    mPosition.y += mGravity;

    // Calcular la velocidad horizontal y vertical a partir de la dirección y la velocidad
    mSpeed.x = mVelocity * std::cos(mDirection);
    mSpeed.y = mVelocity * std::sin(mDirection);

    // Mover el coche en la dirección del vector de velocidad
    mPosition.x += mSpeed.x;
    mPosition.y += mSpeed.y;

    // Verificar si el coche ha colisionado con un obstáculo y aplicar la lógica de colisión

    // Verificar si el coche está haciendo un derrape y aplicar la lógica de derrape
    if (mDrift) {
        // Reducir la fricción del coche para permitir que derrape
        mFriction -= 0.1;
        // Aplicar una fuerza lateral para girar mientras se derrapa
        mDirection += mRotation * 0.5;
    }
    else {
        // Restablecer la fricción normal del coche
        mFriction = 0.1;
    }
}

void VroomVroom::VehicleController::angularSpeed(float deltaX)
{
    if (deltaX != 0) {
        // variables for this method
        Vector3 vNormal = mTransform->up();
        Vector3 position = mTransform->getPosition();
        float tangencialSpeed = mRigidBody->getVelocity().magnitude();
        float radius = tangencialSpeed * maxRadius / maxSpeed;

        // reference turning point
        Vector3 right = mTransform->right().normalize();
        Vector3 turningPoint = position - (right * deltaX * radius); // puede que sea un + en lugar de -
        Vector3 vRadius = turningPoint - position;

        // rotation axis calculate by cross product between vNormal and vRadius
        Vector3 rotationAxis = vNormal.cross(vRadius);

        // angular speed in degrees
        float angularSpeed = tangencialSpeed / radius * (180.0f / MY_PI);
        Vector3 v_squared = mRigidBody->getVelocity() * mRigidBody->getVelocity();

        // make the final rotation
        //mTransform->rotate(angularSpeed, rotationAxis);
        Vector3 centripetalForce = (v_squared / vRadius) * mRigidBody->getMass();
        mRigidBody->addForce(centripetalForce);
        //mRigidBody->addTorque(centripetalForce * vRadius);
    }
}

void VroomVroom::VehicleController::applyRotation(const double& dt, float deltaX)
{
    float tangencialSpeed = mRigidBody->getVelocity().magnitude();
    if (tangencialSpeed > minSpeed) {
        // apply a torque to rotate the body  
        mRigidBody->addTorque(mTransform->up() * deltaX * mRotationSpeed * dt);
        Vector3 w = mRigidBody->getAngularVelocity();
        float w_abs = w.magnitude();

        if (w_abs > maxAngularSpeed) {
            w.normalize();
            mRigidBody->setAngularVelocity(w * maxAngularSpeed);
        }

        // apply a lateral force to the body
        Vector3 velocity = mRigidBody->getVelocity();
        Vector3 lateralDirection = velocity.cross(mTransform->up()).normalize();
        Vector3 lateralForce = lateralDirection * lateralForceFactor * dt;
        mRigidBody->addForce(lateralForce);
    }
}

void VehicleController::setSpeedAndDrift(float speed, float angularSpeed, float driftFactor)
{
    mAcceleration = speed * 2;
    mDeceleration = -speed;
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
    return mVelocity;
}

void VehicleController::onCollisionEnter(me::Entity* other)
{
    if (other->hasComponent("Checkpoint")) {
        Checkpoint* checkpoint = other->getComponent<Checkpoint>("Checkpoint");
        mLastCheckpointPosition = checkpoint->getEntity()->getComponent<Transform>("transform")->getPosition();

#ifdef _DEBUG
        std::cout << "Car " << mPlayerNumber << " has reached checkpoint " << checkpoint->getIndex() << "\n";
#endif

        if (checkpoint->getIndex() == (mCheckpointIndex + 1) % checkpoint->getNumCheckpoints()) {
            //Next checkpoint
            mCheckpointIndex++; 

            if (mCheckpointIndex == checkpoint->getNumCheckpoints()) {
                //Add lap
                mCheckpointIndex = 0;   
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
    if (other->hasComponent("Checkpoint")) {
        Checkpoint* checkpoint = other->getComponent<Checkpoint>("Checkpoint");

        if (checkpoint->getIndex() == mCheckpointIndex + 1)
            mCheckpointIndex++;
        else if (checkpoint->getIndex() == mCheckpointIndex)
            mCheckpointIndex--; //Vas marcha atras por alguna razon
    }
}
