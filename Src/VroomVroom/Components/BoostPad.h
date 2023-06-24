#pragma once
#ifndef __VROOMVROOM_BOOST_PAD
#define __VROOMVROOM_BOOST_PAD


#include "EntityComponent/Component.h"
#include "EntityComponent/FactoryComponent.h"

namespace me {
	class Transform;
	class AudioSource;
}

namespace VroomVroom {

	class FactoryBoostPad : public me::FactoryComponent {
	public:
		me::Component* create(me::Parameters& params) override;
		void destroy(me::Component* component) override;
	};


	/**
	A tile on the ground that gives any racer that drives over it a boost.
	*/
	class BoostPad : public me::Component
	{
	public:
		BoostPad();
		~BoostPad();

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
		void setBoostMaxSpeedMultiplier(float maxSpeedMult);


	private:
		me::AudioSource* mBoostAudio;
		me::Transform* mTransform;

		float mBoostMaxSpeedMultiplier;
	};
}
#endif

