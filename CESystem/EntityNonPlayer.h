#pragma once

#include "Entity.h"
#include "ComponentRender.h"
#include "ComponentMovement.h"
#include "ComponentCollision.h"


class EntityNonPlayer : public Entity
{
public:
	ComponentRender render;
	ComponentMovement movement;
	ComponentCollision collision;

	ComponentRender getComponentRender();
	ComponentMovement getComponentMovement();
	ComponentCollision getComponentCollision();

	void setComponentRender(ComponentRender render);
	void setComponentMovement(ComponentMovement movement);
	void setComponentCollision(ComponentCollision collision);

	EntityNonPlayer();
	~EntityNonPlayer();
};

