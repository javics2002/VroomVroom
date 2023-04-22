#include "Checkpoint.h"
#include "EntityComponent/Entity.h"
#include "EntityComponent/Components/RigidBody.h"

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

	rigidbody = mEntity->addComponent<RigidBody>("rigidbody");
	rigidbody->setTrigger(true);
	rigidbody->setColShape(SHAPES_BOX);
}

void Checkpoint::update()
{
}

void Checkpoint::setSize(Vector3& size)
{
	mSize = size;
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
