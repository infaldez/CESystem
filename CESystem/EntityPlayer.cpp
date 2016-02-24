#include "EntityPlayer.h"


EntityPlayer::EntityPlayer()
{
	render = new ComponentRender(componentKey);
	movement = new ComponentMovement(componentKey);
}


EntityPlayer::~EntityPlayer()
{
}