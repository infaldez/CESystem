#pragma once

#include "Component.h"
#include "Entity.h"
#include "Events.h"
#include <vector>
#include <functional>

class ComponentEvent : public Component
{
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar & boost::serialization::base_object<Component>(*this);
		ar & _collisionEvents;
		ar & _clickEvents;
		ar & _timedEvents;
	}
private:
	std::vector<std::unique_ptr<Event>> _collisionEvents;
	std::vector<std::unique_ptr<Event>> _clickEvents;
	std::vector<std::unique_ptr<Event>> _timedEvents;

public:
	void addCollisionEvent(std::unique_ptr<Event> evnt);
	void addClickEvent(std::unique_ptr<Event> evnt);
	void addTimedEvent(std::unique_ptr<Event> evnt);
	void runCollisionEvents(Entity* a, Entity* b, std::vector<std::unique_ptr<Entity>>& entityList);
	void runClickEvent(Entity* a, sf::Vector2i mousePosition);
	void runTimedEvent(Entity* a, float time, std::vector<std::unique_ptr<Entity>>& entityList);

	ComponentEvent();
	~ComponentEvent();
};

