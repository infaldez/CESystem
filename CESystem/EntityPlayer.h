#pragma once

#include "Entity.h"
#include "ComponentRender.h"
#include "ComponentMovement.h"


class EntityPlayer : public Entity
{
public:
	ComponentRender *render;
	ComponentMovement *movement;

	EntityPlayer();
	~EntityPlayer();
};

