#pragma once

#include "Component.h"

class ComponentPlayerInput : public Component
{
public:
	ComponentPlayerInput(bool(&ckey)[SIZE]);
	~ComponentPlayerInput();



};

