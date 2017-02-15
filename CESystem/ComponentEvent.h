#pragma once

#include "Component.h"
#include "Entity.h"
#include "Events.h"
#include <vector>
#include <functional>

class ComponentEvent : public Component
{
private:
	std::vector<std::function<void(Entity*, Entity*)>> localCollisionEvents;
	std::vector<std::unique_ptr<Event>> globalCollisionEvents;

public:
	void addLocalCollisionEvent(std::function<void(Entity*, Entity*)> colFcn);
	void addGlobalCollisionEvent(std::unique_ptr<Event> e);
	void runLocalCollisionEvents(Entity* a, Entity* b);
	void runGlobalCollisionEvents(std::vector<std::unique_ptr<Entity>>& entityList);

	ComponentEvent();
	~ComponentEvent();
};

