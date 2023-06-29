#pragma once
#ifndef __VROOMVROOM_TIME_FREEZE_RING
#define __VROOMVROOM_TIME_FREEZE_RING


#include "EntityComponent/Component.h"
#include "EntityComponent/FactoryComponent.h"

namespace me {
	class Transform;
	class AudioSource;
}


namespace VroomVroom {

	class CircuitInfo;

	class FactoryTimeFreezeRing : public me::FactoryComponent {
	public:
		me::Component* create(me::Parameters& params) override;
		void destroy(me::Component* component) override;
	};


	/**
	A tile on the ground that gives any racer that drives over it a boost.
	*/
	class TimeFreezeRing : public me::Component
	{
	public:
		TimeFreezeRing();
		~TimeFreezeRing();

		/**
		* Called when the boost pad is spawned in the game to initialize its variables.
		*/
		void start() override;

		/**
		* Called when the boost pad collides with another entity.
		* @param other: a pointer to the entity that the boost pad collided with.
		*/
		void onCollisionEnter(me::Entity* other) override;

		/**
		* Set parameters as necessary for initialization.
		*/
		void setFreezeSecs(float secs);

		/**
		* Set the CircuitInfo linked to the stored Entity name
		*/
		void setCircuitInfo();

		/**
		* Set the CircuitInfo entity's name that'll link to the scene's CircuitInfo
		*/
		void setCircuitInfoName(std::string name);


	private:
		me::AudioSource* mCollisionAudio;
		me::Transform* mTransform;
		CircuitInfo* mCircuitInfo;
		std::string mCircuitInfoName;

		float mFreezeSecs;
	};
}
#endif

