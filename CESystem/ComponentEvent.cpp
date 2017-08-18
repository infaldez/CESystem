#include "ComponentEvent.h"

void ComponentEvent::addCollisionEvent(std::unique_ptr<Event> evnt)
{
	_collisionEvents.push_back(std::move(evnt));
}

void ComponentEvent::addClickEvent(std::unique_ptr<Event> evnt)
{
	_clickEvents.push_back(std::move(evnt));
}

void ComponentEvent::addTimedEvent(std::unique_ptr<Event> evnt)
{
	_timedEvents.push_back(std::move(evnt));
}

void ComponentEvent::runCollisionEvents(Entity* a, Entity* b, std::vector<std::unique_ptr<Entity>>& entityList)
{
	for (auto& e : _collisionEvents)
		e->executeCollisionEvents(a, b, entityList);
}

void ComponentEvent::runClickEvent(Entity* a, sf::Vector2i mousePosition)
{
	for (auto& e : _clickEvents)
		e->executeClick(a, mousePosition);
}

void ComponentEvent::runTimedEvent(Entity* a, float time, std::vector<std::unique_ptr<Entity>>& entityList)
{
	for (auto& e : _timedEvents)
		e->executeTimedEvent(a, time, entityList);
}

ComponentEvent::ComponentEvent() 
	: Component(components::COMPONENT_EVENT)
{
}


ComponentEvent::~ComponentEvent()
{
}
