#include "EntityNonPlayer.h"


EntityNonPlayer::EntityNonPlayer()
	: render(componentKey), movement(componentKey),
	collision(componentKey)
{

}


EntityNonPlayer::~EntityNonPlayer()
{
}


ComponentRender EntityNonPlayer::getComponentRender()
{
	return render;
}


ComponentMovement EntityNonPlayer::getComponentMovement()
{
	return movement;
}


ComponentCollision EntityNonPlayer::getComponentCollision()
{
	return collision;
}


void EntityNonPlayer::setComponentRender(ComponentRender render)
{
	this->render = render;
}


void EntityNonPlayer::setComponentMovement(ComponentMovement movement)
{
	this->movement = movement;
}


void EntityNonPlayer::setComponentCollision(ComponentCollision collision)
{
	this->collision = collision;
}