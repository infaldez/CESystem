#include "EntityPlayer.h"


EntityPlayer::EntityPlayer()
{
	//render = new ComponentRender(componentKey);
	//movement = new ComponentMovement(componentKey);
	//collision = new ComponentCollision(componentKey);
	//playerInput = new ComponentPlayerInput(componentKey);

	addComponent(render = new ComponentRender(componentKey));
	addComponent(movement = new ComponentMovement(componentKey));
	addComponent(collision = new ComponentCollision(componentKey));
	addComponent(playerInput = new ComponentPlayerInput(componentKey));
}


EntityPlayer::~EntityPlayer()
{
}