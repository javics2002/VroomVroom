#pragma once

#ifndef __VROOMVROOM_CHECKPOINT
#define __VROOMVROOM_CHECKPOINT

#include "EntityComponent/Components/Component.h"
#include "Utils/Vector3.h"

namespace me {
	class RigidBody;
}

/*
A checkpoint is a cube trigger with an index, that checks the players that go
through it and update their circuit progress. 
*/
class Checkpoint : public me::Component
{
	//Number of checkpoint
	static int mNumCheckpoints;

	int mIndex;
	me::Vector3 mSize;

	me::RigidBody* rigidbody = nullptr;

public:
	Checkpoint();
	~Checkpoint();

	void start() override;
	void update() override;

	void setSize(me::Vector3& size);
};
#endif

