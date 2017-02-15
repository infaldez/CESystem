#include "ComponentEvent.h"


void ComponentEvent::addLocalCollisionEvent(std::function<void(Entity*, Entity*)> colFcn)
{
	localCollisionEvents.push_back((colFcn));
}

void ComponentEvent::addGlobalCollisionEvent(std::function<void(std::vector<std::unique_ptr<Entity>>&)> colFcn)
{
	globalCollisionEvents.push_back(colFcn);
}

void ComponentEvent::runLocalCollisionEvents(Entity* a, Entity* b)
{
	for (auto& colFnc : localCollisionEvents)
		colFnc(a, b);
}

void ComponentEvent::runGlobalCollisionEvents(std::vector<std::unique_ptr<Entity>>& entityList)
{
	for (auto& colFnc : globalCollisionEvents)
		colFnc(entityList);
}

ComponentEvent::ComponentEvent() 
	: Component(components::COMPONENT_EVENT)
{
}


ComponentEvent::~ComponentEvent()
{
}
