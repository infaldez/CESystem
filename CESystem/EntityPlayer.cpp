#include "EntityPlayer.h"


EntityPlayer::EntityPlayer()
{
	render = new ComponentRender(componentKey);
}


EntityPlayer::~EntityPlayer()
{
}