#pragma once

#include "Entity.h"
#include "ComponentRender.h"


class EntityPlayer : public Entity
{
public:
	ComponentRender *render;

	EntityPlayer();
	~EntityPlayer();
};