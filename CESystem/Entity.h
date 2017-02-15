#pragma once

#include "Component.h"
#include "ComponentRender.h"
#include "ComponentMovement.h"
#include "ComponentCollision.h"
#include "ComponentPlayerInput.h"
#include "ComponentAABB.h"
#include "ComponentPosition.h"

#include <vector>
#include <iostream>
#include <memory>
#include<array>

class Entity
{
private:
	std::vector<std::unique_ptr<Component>> _components;
	std::vector<std::string> _tags;

public:
	std::array<bool, components::SIZE> componentKey;
	
	Entity();
	~Entity();

	void addComponent(std::unique_ptr<Component> component);
	void addTag(std::string tag);
	bool hasTag(std::string tag);

	template <class cType>
	cType* getComponent(components::id cId)
	{
		if (componentKey[cId] == true)
		{
			for (std::size_t i = 0; i != _components.size(); ++i)
			{
				if (_components.at(i)->cId == cId)
					return (cType*)_components.at(i).get();
			}
		}
		return nullptr;
	}

};