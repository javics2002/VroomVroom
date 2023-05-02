#pragma once
#ifndef __VROOMVROOM_NERF
#define __VROOMVROOM_NERF

#include "PowerUp.h"
#include "EntityComponent/Components/Component.h"
#include "Utils/Vector3.h"


namespace me {
	class Entity;
	class Transform;
	class RigidBody;
	class Timer;
}

namespace VroomVroom {
	/**
Throws an oil barrel that makes an oil puddle behind the player and
makes the first car that drives on it lose control, and then disappears.
*/
	class Nerf : public PowerUp
	{
	private:
		bool isActive;

		me::Transform* mTransform;
		me::RigidBody* mRigidBody;
		me::Vector3 vForward;
		me::Timer* mTimer;
		float mLostControl;
		bool mHit;
		me::Entity* mHitCar;
		me::Entity* mUsedCar;
		float mSpeed;

	public:
		Nerf();
		~Nerf();

		void start() override;
		void update(const double& dt) override;

		void setSpeed(float speed);

		void setLostControl(float lost);

		// Overrides the PowerUp class functions
		void onCollisionEnter(me::Entity* other) override;

		void use(me::Entity* other) override;

	};
}
#endif