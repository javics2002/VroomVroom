#include "WheelController.h"
#include "VehicleController.h"
#include "Input/InputManager.h"
#include "EntityComponent/Entity.h"
#include "EntityComponent/Components/Transform.h"
#include "Utils/Vector3.h"

using namespace me;
using namespace VroomVroom;

WheelController::WheelController()
{
	mXRotation = 0;
	mYRotation = 0;
	mSpeed = 0.05f;
}

WheelController::~WheelController()
{
}


void WheelController::update(const double& dt)
{
	bool left = me::inputManager().getButton("LEFT");
	bool right = me::inputManager().getButton("RIGHT");

	float deltaX = inputManager().getAxis("HORIZONTAL");

	//Rotación en Y para el giro
	if (mYRotation < Y_ROTATION_THRESHOLD && mYRotation >= 0) {
		if (left || deltaX > 0) { //Es posible que haya que intercambiar los < > de los deltaX al revés.
			mEntity->getComponent<Transform>("transform")->rotate(+Y_STEP_ROTATION, { 0, 1, 0 });
			mYRotation += Y_STEP_ROTATION;
		}
		else if (right || deltaX < 0) {
			mEntity->getComponent<Transform>("transform")->rotate(-Y_STEP_ROTATION, { 0, 1, 0 });
			mYRotation += Y_STEP_ROTATION;
		}
		else {
			mYRotation -= Y_STEP_ROTATION;
		}
	}

	bool acelerate = inputManager().getButton("ACELERATE");
	bool decelerate = inputManager().getButton("DECELERATE");

	//Rotación en Z para la aceleracion

	mSpeed = mEntity->getComponent<VehicleController>("vehiclecontroller")->getSpeed();
	if (acelerate) {
		mEntity->getComponent<Transform>("transform")->rotate(mSpeed * Z_ROTATION_FACTOR, { 0, 0, 1 });
	}
	else if (decelerate) {
		mEntity->getComponent<Transform>("transform")->rotate(-mSpeed * Z_ROTATION_FACTOR, { 0, 0, 1 });
	}

}