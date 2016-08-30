#pragma once

#include "Component.h"
#include "ComponentRender.h"
#include "ComponentMovement.h"
#include "ComponentCollision.h"
#include "ComponentPlayerInput.h"

#include <vector>
#include <iostream>


class Entity
{
private:
	ComponentRender* nullRender = NULL;
	ComponentMovement* nullMovement = NULL;
	ComponentCollision* nullCollision = NULL;
	ComponentPlayerInput* nullInput = NULL;

	std::vector<Component*> _components;

public:
	bool componentKey[components::SIZE];
	
	virtual ComponentRender getComponentRender() { return *nullRender; };
	virtual ComponentMovement getComponentMovement() { return *nullMovement; };
	virtual ComponentCollision getComponentCollision() { return *nullCollision; };
	virtual ComponentPlayerInput getComponentPlayerInput() { return *nullInput; };

	virtual void setComponentRender(ComponentRender render) {};
	virtual void setComponentMovement(ComponentMovement movement) {};
	virtual void setComponentCollision(ComponentCollision collision) {};
	virtual void setComponentPlayerInput(ComponentPlayerInput input) {};

	template <class cType> 
	cType* getComponent(components::id cId)
	{
		if (componentKey[cId] == true)
		{
			for (int i = 0; i < _components.size(); i++)
			{
				if (_components.at(i)->cId == cId)
				{
					return (cType*)_components.at(i);
				}
			}
		}
	}

	void addComponent(Component* component)
	{	
		if (componentKey[component->cId] == false)
		{
			componentKey[component->cId] = true;
			_components.push_back(component);	
		}		
	}

	Entity();
	~Entity();
};