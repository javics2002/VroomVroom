#pragma once
#ifndef __VROOMVROOM_VROOMVROOMCOMPONENTS
#define __VROOMVROOM_VROOMVROOMCOMPONENTS

#include "EntityComponent/Components/FactoryComponent.h"

class FactoryCameraFollow : public me::FactoryComponent {
public:
	me::Component* create(me::Parameters params) override;
};

class FactoryVehicleController : public me::FactoryComponent {
public:
	me::Component* create(me::Parameters params) override;
};

//CirtuitoInfo

//GameManager

class FactoryCheckpoint : public me::FactoryComponent {
public:
	me::Component* create(me::Parameters params) override;
};
#endif