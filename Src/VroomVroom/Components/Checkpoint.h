#pragma once

#ifndef __VROOMVROOM_CHECKPOINT
#define __VROOMVROOM_CHECKPOINT

#include "EntityComponent/Components/Component.h"
#include "Utils/Vector3.h"

namespace me {
	class Checkpoint : public Component
	{
	public:
		Checkpoint();
		~Checkpoint();

		void start() override;
		void update() override;
	};
}
#endif

