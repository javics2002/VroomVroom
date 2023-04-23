#include "Checkpoint.h"
#include "EntityComponent/Entity.h"
#include "EntityComponent/Components/RigidBody.h"
#include "EntityComponent/Components/Collider.h"

using namespace me;
using namespace VroomVroom;

int Checkpoint::MNumCheckpoints = 0;

Checkpoint::Checkpoint()
{
}

Checkpoint::~Checkpoint()
{
	MNumCheckpoints--; //pasar a la futura destructora
}

void Checkpoint::start()
{
	mIndex = MNumCheckpoints++;
}

void Checkpoint::setIndex(int index)
{
	mIndex = index;
}

int Checkpoint::getIndex()
{
	return mIndex;
}

void Checkpoint::setNumCheckpoints(int numCheckpoints)
{
	MNumCheckpoints = numCheckpoints;
}

int Checkpoint::getNumCheckpoints()
{
	return MNumCheckpoints;
}
