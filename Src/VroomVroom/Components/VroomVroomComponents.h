#pragma once
#ifndef __VROOMVROOM_VROOMVROOMCOMPONENTS
#define __VROOMVROOM_VROOMVROOMCOMPONENTS

#include "EntityComponent/Components/FactoryComponent.h"

namespace VroomVroom {
	/**
	Single factories for components created in Vroom Vroom solution
	*/

	class FactoryCameraFollow : public me::FactoryComponent {
	public:
		me::Component* create(me::Parameters& params) override;
		void destroy(me::Component* component) override;
	};

	class FactoryVehicleController : public me::FactoryComponent {
	public:
		me::Component* create(me::Parameters& params) override;
		void destroy(me::Component* component) override;
	};

	class FactoryWheelController : public me::FactoryComponent {
	public:
		me::Component* create(me::Parameters& params) override;
		void destroy(me::Component* component) override;
	};

	class FactoryCirtuitInfo : public me::FactoryComponent {
	public:
		me::Component* create(me::Parameters& params) override;
		void destroy(me::Component* component) override;
	};

	class FactoryGameManager : public me::FactoryComponent {
	public:
		me::Component* create(me::Parameters& params) override;
		void destroy(me::Component* component) override;
	};

	class FactoryCheckpoint : public me::FactoryComponent {
	public:
		me::Component* create(me::Parameters& params) override;
		void destroy(me::Component* component) override;
	};

	class FactoryOil : public me::FactoryComponent {
	public:
		me::Component* create(me::Parameters& params) override;
		void destroy(me::Component* component) override;
	};

	class FactoryNerf : public me::FactoryComponent {
	public:
		me::Component* create(me::Parameters& params) override;
		void destroy(me::Component* component) override;
	};

	class FactoryUIButtonScene : public me::FactoryComponent {
	public:
		me::Component* create(me::Parameters& params) override;
		void destroy(me::Component* component) override;
	};

	class FactoryUIButtonQuit : public me::FactoryComponent {
	public:
		me::Component* create(me::Parameters& params) override;
		void destroy(me::Component* component) override;
	};

	class FactoryPowerUpUIWheel : public me::FactoryComponent {
		public:
		me::Component* create(me::Parameters& params) override;
		void destroy(me::Component* component) override;
	};
	
	class FactoryPowerUpObject : public me::FactoryComponent {
	public:
		me::Component* create(me::Parameters& params) override;
		void destroy(me::Component* component) override;
	};
}
#endif