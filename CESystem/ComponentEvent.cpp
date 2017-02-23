#include "ComponentEvent.h"

void ComponentEvent::addLocalCollisionEvent(std::unique_ptr<Event> evnt)
{
	_localCollisionEvents.push_back(std::move(evnt));
}

void ComponentEvent::addGlobalCollisionEvent(std::unique_ptr<Event> evnt)
{
	_globalCollisionEvents.push_back(std::move(evnt));
}

void ComponentEvent::runLocalCollisionEvents(Entity* a, Entity* b)
{
	for (auto& e : _localCollisionEvents)
		e->executeLocal(a, b);
}

void ComponentEvent::runGlobalCollisionEvents(std::vector<std::unique_ptr<Entity>>& entityList)
{
	for (auto& e : _globalCollisionEvents)
	{
		e->executeGlobal(entityList);
	}
}

ComponentEvent::ComponentEvent() 
	: Component(components::COMPONENT_EVENT)
{
}


ComponentEvent::~ComponentEvent()
{
}
