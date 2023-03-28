#pragma once
#ifndef __VROOMVROOM_VROOMVROOMCOMPONENTS
#define __VROOMVROOM_VROOMVROOMCOMPONENTS

#include "EntityComponent/Components/FactoryComponent.h"

/**
Single factories for components that created in Vroom Vroom solution

*/
//return a CameraFollow as component
class FactoryCameraFollow : public me::FactoryComponent {
public:
	me::Component* create(me::Parameters params) override;
};
//return a VehicleController as component
class FactoryVehicleController : public me::FactoryComponent {
public:
	me::Component* create(me::Parameters params) override;
};
//return a WheelController as component
class FactoryWheelController : public me::FactoryComponent {
public:
	me::Component* create(me::Parameters params) override;
};
//return a CirtuitoInfo as component
class FactoryCirtuitoInfo : public me::FactoryComponent {
public:
	me::Component* create(me::Parameters params) override;
};
//return a GameManager as component
class FactoryGameManager : public me::FactoryComponent {
public:
	me::Component* create(me::Parameters params) override;
};
//return a Checkpoint as component
class FactoryCheckpoint : public me::FactoryComponent {
public:
	me::Component* create(me::Parameters params) override;
};
#endif