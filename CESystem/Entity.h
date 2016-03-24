#pragma once

#include "Component.h"
#include "ComponentRender.h"
#include "ComponentMovement.h"
#include "ComponentCollision.h"
#include "ComponentPlayerInput.h"

#include <vector>

class Entity
{
private:
	ComponentRender* nullRender = NULL;
	ComponentMovement* nullMovement = NULL;
	ComponentCollision* nullCollision = NULL;
	ComponentPlayerInput* nullInput = NULL;

public:
	bool componentKey[components::SIZE];
	
	virtual ComponentRender getComponentRender() { return *nullRender; };
	virtual ComponentMovement getComponentMovement() { return *nullMovement; };
	virtual ComponentCollision getComponentCollision() { return *nullCollision; };
	virtual ComponentPlayerInput getComponentPlayerInput() { return *nullInput; };

	virtual void setComponentRender(ComponentRender render) {};
	virtual void setComponentMovement(ComponentMovement movement) {};
	virtual void setComponentCollision(ComponentCollision collision) {};
	virtual void setComponentPlayerInput(ComponentPlayerInput input) {};

	Entity();
	~Entity();
};