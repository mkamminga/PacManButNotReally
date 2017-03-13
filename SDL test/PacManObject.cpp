#include "PacManObject.h"
#include "PacManBaseState.h"

void PacManObject::update(double deltaTime)
{
	if (!currentState) 
	{
		currentState = std::make_shared<PacManBaseState>(this->shared_from_this());
	}

	currentState->update(deltaTime);
}
