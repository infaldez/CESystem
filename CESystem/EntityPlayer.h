#pragma once

#include "Entity.h"
#include "ComponentRender.h"
#include "ComponentMovement.h"
#include "ComponentCollision.h"


class EntityPlayer : public Entity
{
public:
	ComponentRender *render;
	ComponentMovement *movement;
	ComponentCollision *collision;

	EntityPlayer();
	~EntityPlayer();
};

