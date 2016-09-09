#pragma once

#include "Component.h"
#include "ComponentRender.h"
#include "ComponentMovement.h"
#include "ComponentCollision.h"
#include "ComponentPlayerInput.h"

#include <vector>
#include <iostream>

#include<array>

class Entity
{
private:
	std::vector<Component*> _components;

public:
	std::array<bool, components::SIZE> componentKey;
	
	Entity();
	~Entity();

	void addComponent(Component* component);

	template <class cType>
	cType* getComponent(components::id cId)
	{
		if (componentKey[cId] == true)
		{
			for (int i = 0; i < _components.size(); i++)
			{
				if (_components.at(i)->cId == cId)
					return (cType*)_components.at(i);
			}
		}
	}

};