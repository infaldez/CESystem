#pragma once

#include "Entity.h"
#include "ComponentRender.h"
#include "ComponentMovement.h"
#include "ComponentCollision.h"
#include "ComponentPlayerInput.h"


class EntityPlayer : public Entity
{
public:
	/*ComponentRender render;
	ComponentMovement movement;
	ComponentCollision collision;
	ComponentPlayerInput playerInput;

	ComponentRender getComponentRender();
	ComponentMovement getComponentMovement();
	ComponentCollision getComponentCollision();
	ComponentPlayerInput getComponentPlayerInput();

	void setComponentRender(ComponentRender render);
	void setComponentMovement(ComponentMovement movement);
	void setComponentCollision(ComponentCollision collision);
	void setComponentPlayerInput(ComponentPlayerInput input);
	*/

	EntityPlayer();
	~EntityPlayer();
};

