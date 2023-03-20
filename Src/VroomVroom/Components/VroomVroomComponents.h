#pragma once
#ifndef __VROOMVROOM_VROOMVROOMCOMPONENTS
#define __VROOMVROOM_VROOMVROOMCOMPONENTS

#include "EntityComponent/Components/FactoryComponent.h"

class FactoryCameraFollow : public me::FactoryComponent {
public:
	me::Component* create(Parameters params);

};

class FactoryVehicleController : public me::FactoryComponent {
public:
	me::Component* create(Parameters params);

};
#endif