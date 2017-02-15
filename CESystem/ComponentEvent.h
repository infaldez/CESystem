#pragma once

#include "Component.h"
#include "Entity.h"
#include <vector>
#include <functional>

class ComponentEvent : public Component
{
private:
	std::vector<std::function<void(Entity*, Entity*)>> localCollisionEvents;
	std::vector<std::function<void(std::vector<std::unique_ptr<Entity>>&)>> globalCollisionEvents;

public:
	void addLocalCollisionEvent(std::function<void(Entity*, Entity*)> colFcn);
	void addGlobalCollisionEvent(std::function<void(std::vector<std::unique_ptr<Entity>>&)> entityList);
	void runLocalCollisionEvents(Entity* a, Entity* b);
	void runGlobalCollisionEvents(std::vector<std::unique_ptr<Entity>>& entityList);

	ComponentEvent();
	~ComponentEvent();
};

