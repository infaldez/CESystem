#include "Entity.h"


Entity::Entity()
{	
	for (int i = 0; i < components::SIZE; i++) {
		componentKey[i] = false;
	}
}


Entity::~Entity()
{
}


void Entity::addComponent(std::unique_ptr<Component> component)
{
	if (componentKey[component->cId] == false)
	{
		componentKey[component->cId] = true;
		_components.push_back(std::move(component));
	}
}

