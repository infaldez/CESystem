#include "Entity.h"
#include <algorithm>


Entity::Entity()
{	
	for (int i = 0; i < components::SIZE; i++) {
		componentKey[i] = false;
	}
	
	_save = true;
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


void Entity::addTag(std::string tag)
{
	_tags.push_back(tag);
}


bool Entity::hasTag(std::string tag)
{
	return std::find(_tags.begin(), _tags.end(), tag) != _tags.end();
}

void Entity::setSave(bool save)
{
	_save = save;
}

bool Entity::getSave()
{
	return _save;
}

