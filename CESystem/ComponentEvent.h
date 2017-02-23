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
		ar & _localCollisionEvents;
		ar & _globalCollisionEvents;
	}
private:
	std::vector<std::unique_ptr<Event>> _localCollisionEvents;
	std::vector<std::unique_ptr<Event>> _globalCollisionEvents;

public:
	void addLocalCollisionEvent(std::unique_ptr<Event> evnt);
	void addGlobalCollisionEvent(std::unique_ptr<Event> evnt);
	void runLocalCollisionEvents(Entity* a, Entity* b);
	void runGlobalCollisionEvents(std::vector<std::unique_ptr<Entity>>& entityList);

	ComponentEvent();
	~ComponentEvent();
};

