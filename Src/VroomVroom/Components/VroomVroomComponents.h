#pragma once
#ifndef __VROOMVROOM_VROOMVROOMCOMPONENTS
#define __VROOMVROOM_VROOMVROOMCOMPONENTS

#include "EntityComponent/Components/FactoryComponent.h"

namespace me {
	class FactoryCameraFollow : public FactoryComponent {
	public:
		Component* create(Parameters params) override;
	};

	class FactoryVehicleController : public FactoryComponent {
	public:
		Component* create(Parameters params) override;
	};
}
#endif