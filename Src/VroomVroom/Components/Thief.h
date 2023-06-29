#pragma once
#ifndef __VROOMVROOM_THIEF
#define __VROOMVROOM_THIEF

#include "PowerUp.h"


namespace me {
	class Entity;
	class Timer;
	class AudioSource;
}

namespace VroomVroom {


	class FactoryThief : public me::FactoryComponent {
	public:
		me::Component* create(me::Parameters& params) override;
		void destroy(me::Component* component) override;
	};

	/**
	Throws a proyectil that moves forward, if it collide with another player,
	this will loose control of his car for a seconds.
	*/
	class Thief : public PowerUp
	{
	private:
		me::Timer* mTimer;
		float mSpeed;

		me::AudioSource* mThiefSound;

	public:
		Thief();
		~Thief();

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