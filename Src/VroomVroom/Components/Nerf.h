#pragma once
#ifndef __VROOMVROOM_NERF
#define __VROOMVROOM_NERF

#include "PowerUp.h"
#include "EntityComponent/Components/Component.h"
#include "Utils/Vector3.h"


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

		void setSpeed(float speed);

		// Overrides the PowerUp class functions
		void onCollisionEnter(me::Entity* other) override;

		void use(me::Entity* other) override;

	};
}
#endif