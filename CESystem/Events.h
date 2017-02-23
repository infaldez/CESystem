#pragma once

#include "Entity.h"
#include "componentDamage.h"
#include "ComponentHealth.h"

#include <boost/serialization/access.hpp>
/*
	GLOBAL Event base
*/
class Event
{
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
	}

public:
	virtual void executeGlobal(std::vector<std::unique_ptr<Entity>>& entityList){}
	virtual void executeLocal(Entity* a, Entity* b){}

	Event(){}
	virtual ~Event(){};
};


/*
	LOCAL COLLISION EVENTS
*/
class DoDamage : public Event
{
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar & boost::serialization::base_object<Event>(*this);
	}
public:
	virtual void executeLocal(Entity* a, Entity* b)
	{
		if (a->componentKey[components::COMPONENT_DAMAGE] == true &&
			b->componentKey[components::COMPONENT_HEALTH] == true)
		{
			ComponentHealth* health = b->getComponent<ComponentHealth>(components::COMPONENT_HEALTH);
			componentDamage* dmg = a->getComponent<componentDamage>(components::COMPONENT_DAMAGE);

			health->setHealth(health->getHealth() - dmg->getDamage());
			a->componentKey[components::DELETE] = true;
			if (health->getHealth() <= 0)
			{
				b->componentKey[components::DELETE] = true;
			}
		}
	}
	
	DoDamage(){}
	~DoDamage(){}
};


/*
	GLOBAL COLLISION EVENTS
	*/
class MoveBlock : public Event
{
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar & boost::serialization::base_object<Event>(*this);
		ar & tag & position.x & position.y;
	}

public:
	std::string tag;
	sf::Vector2f position;

	virtual void executeGlobal(std::vector<std::unique_ptr<Entity>>& entityList)
	{
		for (auto& ent : entityList)
		{
			if (ent->hasTag(tag))
			{
				auto cPosition = ent->getComponent<ComponentPosition>(components::COMPONENT_POSITION);
				sf::Vector2f p = cPosition->getPosition();
				cPosition->setPosition(position);
			}
		}
	}

	MoveBlock(){}
	MoveBlock(std::string tag, sf::Vector2f position) : tag(tag), position(position) {}
	~MoveBlock(){}
};