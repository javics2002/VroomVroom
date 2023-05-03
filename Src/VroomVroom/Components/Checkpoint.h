#pragma once

#ifndef __VROOMVROOM_CHECKPOINT
#define __VROOMVROOM_CHECKPOINT

#include "EntityComponent/Components/Component.h"

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

		/**
		* Sets the index of the checkpoint.
		* @param index The index of the checkpoint.
		*/
		void setIndex(int index);

		/**
		* Gets the index of the checkpoint.
		* @return The index of the checkpoint.
		*/
		int getIndex();

		/**
		* Sets the total number of checkpoints.
		* @param numCheckpoints The total number of checkpoints.
		*/
		static void SetNumCheckpoints(int numCheckpoints);

		/**
		* Gets the total number of checkpoints.
		* @return The total number of checkpoints.
		*/
		static int GetNumCheckpoints();
	};
}
#endif

