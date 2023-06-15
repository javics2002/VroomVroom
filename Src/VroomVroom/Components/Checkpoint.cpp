#include "Checkpoint.h"
#include "EntityComponent/Entity.h"
#include "MotorEngine/Scene.h"
#include "CircuitInfo.h"
#include "MotorEngine/MotorEngineError.h"
#include "MotorEngine/SceneManager.h"

using namespace me;
using namespace VroomVroom;


Component* FactoryCheckpoint::create(Parameters& params)
{
	Checkpoint* checkpoint = new Checkpoint();

	checkpoint->setIndex(Value(params, "index", Checkpoint::GetNumCheckpoints()));

	return checkpoint;
}

void FactoryCheckpoint::destroy(Component* component)
{
	delete component;
}


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

	if (!mEntity->getScene()->findEntity("circuit").get()) {
		errorManager().throwMotorEngineError("Checkpoint error", "Circuit entity was not found");
		sceneManager().quit();
        return;
	}


	Entity* circuitEntity = mEntity->getScene()->findEntity("circuit").get();
	if (!circuitEntity) {
		errorManager().throwMotorEngineError("Checkpoint error", "Circuit entity doesn't exist.");
		sceneManager().quit();
		return;
	}

	mCircuitInfo = circuitEntity->getComponent<CircuitInfo>("circuitinfo");

	if (!mCircuitInfo) {
		errorManager().throwMotorEngineError("Checkpoint error", "Circuit entity doesn't have CircuitInfo component");
		sceneManager().quit();
        return;
	}

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
