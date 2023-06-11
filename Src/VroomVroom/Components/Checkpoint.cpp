#include "Checkpoint.h"
#include "EntityComponent/Entity.h"
#include "MotorEngine/Scene.h"
#include "CircuitInfo.h"

using namespace me;
using namespace VroomVroom;

int Checkpoint::MNumCheckpoints = 0;

Checkpoint::Checkpoint()
{
}

Checkpoint::~Checkpoint()
{
	MNumCheckpoints--;
}

void Checkpoint::start()
{
	MNumCheckpoints++;

	mCircuitInfo = mEntity->getScene()->findEntity("circuit").get()->getComponent<CircuitInfo>("circuitinfo");
	mCircuitInfo->addCheckpoint(this);
}

void Checkpoint::setIndex(int index)
{
	mIndex = index;
}

int Checkpoint::getIndex()
{
	return mIndex;
}

void Checkpoint::SetNumCheckpoints(int numCheckpoints)
{
	MNumCheckpoints = numCheckpoints;
}

int Checkpoint::GetNumCheckpoints()
{
	return MNumCheckpoints;
}
