#include "ComponentPlayerInput.h"


ComponentPlayerInput::ComponentPlayerInput(bool(&ckey)[SIZE])
{
	ckey[COMPONENT_INPUT] = true;
}


ComponentPlayerInput::~ComponentPlayerInput()
{
}
