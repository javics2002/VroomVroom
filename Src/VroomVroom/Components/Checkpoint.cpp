#include "Checkpoint.h"
#include "EntityComponent/Entity.h"
#include "EntityComponent/Components/RigidBody.h"

using namespace me;

int Checkpoint::mNumCheckpoints = 0;

Checkpoint::Checkpoint()
{
}

Checkpoint::~Checkpoint()
{
	mNumCheckpoints--; //pasar a la futura destructora
}

void Checkpoint::start()
{
	mIndex = mNumCheckpoints++;

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
