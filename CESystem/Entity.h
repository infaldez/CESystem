#pragma once

#include "Component.h"

#include <vector>

class Entity
{
private:
	std::vector<Component*> m_components;

public:
	static bool componentKey[components::SIZE];
	
	std::vector<Component*> getComponents();
	void addComponent(Component* comp);

	Entity();
	~Entity();
};