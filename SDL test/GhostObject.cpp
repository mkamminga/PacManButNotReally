#include "GhostObject.h"
#include "PacManBaseState.h"

void GhostObject::update(double deltaTime)
{
	if (!currentState)
	{
		currentState = std::make_unique<PacManBaseState>(this->shared_from_this());
	}

	currentState->update(deltaTime);
}
