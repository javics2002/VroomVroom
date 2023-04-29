#pragma once

#ifndef __VROOMVROOM_CHECKPOINT
#define __VROOMVROOM_CHECKPOINT

#include "EntityComponent/Components/Component.h"
#include "Utils/Vector3.h"

namespace me {
	class RigidBody;
}

namespace VroomVroom {
	class CircuitInfo;

	/*
	A checkpoint is a cube trigger with an index, that checks the players that go
	through it and update their circuit progress.
	*/
	class Checkpoint : public me::Component
	{
		//Number of checkpoint
		static int MNumCheckpoints;

		int mIndex;

		me::RigidBody* rigidbody = nullptr;
		CircuitInfo* mCircuitInfo = nullptr;

	public:
		Checkpoint();
		~Checkpoint();

		void start() override;

		void setIndex(int index);
		int getIndex();

		static void SetNumCheckpoints(int numCheckpoints);
		static int GetNumCheckpoints();
	};
}
#endif

