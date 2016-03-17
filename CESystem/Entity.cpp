#include "Entity.h"


Entity::Entity()
{
}


Entity::~Entity()
{
}


std::vector<Component*> Entity::getComponents()
{
	return m_components;
}


void Entity::addComponent(Component* comp)
{
	m_components.push_back(comp);
}


bool Entity::componentKey[components::SIZE] = { false };