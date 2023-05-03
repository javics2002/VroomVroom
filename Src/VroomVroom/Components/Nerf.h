#pragma once
#ifndef __VROOMVROOM_NERF
#define __VROOMVROOM_NERF

#include "PowerUp.h"

namespace me {
	class Entity;
	class Timer;
	class AudioSource;
}

namespace VroomVroom {
	/**
	Throws an oil barrel that makes an oil puddle behind the player and
	makes the first car that drives on it lose control, and then disappears.
	*/
	class Nerf : public PowerUp
	{
	private:
		me::Timer* mTimer;
		float mSpeed;

		me::AudioSource* mNerfSound;

	public:
		Nerf();
		~Nerf();

		void start() override;
		void update(const double& dt) override;

		/**
		 * Sets the speed at which the Nerf power-up is thrown.
		 * @param speed The speed at which the Nerf power-up is thrown.
		 */
		void setSpeed(float speed);

		/**
		 * Handles collision with other entities. If the entity is a car, the Nerf power-up is used.
		 * @param other The other entity involved in the collision.
		 */
		void onCollisionEnter(me::Entity* other) override;

		/**
		 * Uses the Nerf power-up on the given entity
		 * @param other The entity on which to use the Nerf power-up.
		 */
		void use(me::Entity* other) override;

	};
}
#endif