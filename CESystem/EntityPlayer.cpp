#include "EntityPlayer.h"


EntityPlayer::EntityPlayer()
{
	render = new ComponentRender(componentKey);
	movement = new ComponentMovement(componentKey);
	collision = new ComponentCollision(componentKey);
}


EntityPlayer::~EntityPlayer()
{
}