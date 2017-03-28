#pragma once

#include "Entity.h"
#include "Game.h"
#include <boost/serialization/access.hpp>
#include <string>
/*
	Event base
*/
class Event
{
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
	}

public:
	virtual void executeCollisionEvents(Entity* a, Entity* b, std::vector<std::unique_ptr<Entity>>& entityList){}
	virtual void executeClick(Entity* a, sf::Vector2i mpos){}
	virtual void executeTimedEvent(Entity* a, float time){}

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
	virtual void executeCollisionEvents(Entity* a, Entity* b, std::vector<std::unique_ptr<Entity>>& entityList);
	
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

	virtual void executeCollisionEvents(Entity* a, Entity* b, std::vector<std::unique_ptr<Entity>>& entityList);

	MoveBlock(){}
	MoveBlock(std::string tag, sf::Vector2f position) : tag(tag), position(position) {}
	~MoveBlock(){}
};

template<typename T>
class Click : public Event
{
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar & boost::serialization::base_object<Event>(*this);
	}
public:	
	std::function<T(void)> _lcFunc;

	void executeClick(Entity* a, sf::Vector2i mpos)
	{
		ComponentAABB* aabb = a->getComponent<ComponentAABB>(components::COMPONENT_AABB);
		ComponentPosition* cpos = a->getComponent<ComponentPosition>(components::COMPONENT_POSITION);

		sf::Vector2f pos = cpos->getPosition();
		sf::Vector2f size = aabb->getExtents();
		sf::Vector2f colPos = aabb->getPosition(pos);

		// Check if there's AABB overlap
		if (colPos.x < mpos.x &&
			colPos.x + size.x > mpos.x &&
			colPos.y < mpos.y &&
			colPos.y + size.y > mpos.y)
		{
			_lcFunc();
		}
	}

	Click(){};
	Click(std::function<T(void)> lcFunc) : _lcFunc(lcFunc){}

	~Click(){}
};


class EntityManager;
class Save : public Event
{
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar & boost::serialization::base_object<Event>(*this);
	}
public:
	virtual void executeClick(Entity* a, sf::Vector2i mpos);
	EntityManager* em;
	std::string name;

	Save(){}
	Save(std::string name, EntityManager& em);;
	~Save(){}
};

class PathSequence : public Event
{
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar & boost::serialization::base_object<Event>(*this);
	}

public:
	enum seqCondition
	{
		TIME,
		X,
		Y
	};

	struct SeqItem
	{
		float transitionValue;
		float rotation;
		float speed;
		seqCondition transitionCondition;
	};

	std::vector<SeqItem> _sequence;
	float previousSequenceTime;
	sf::Vector2f startingDistance;
	seqCondition _condition;
	virtual void executeTimedEvent(Entity* a, float time);

	PathSequence(std::vector<SeqItem> sequence, Entity* entity) : _sequence(sequence) {
		_seq = _sequence.begin();
		previousSequenceTime = 0;

		if (entity->componentKey[components::COMPONENT_MOVEMENT] == true && entity->componentKey[components::COMPONENT_POSITION])
		{
			// Init the entity with values from first sequence
			entity->getComponent<ComponentMovement>(components::COMPONENT_MOVEMENT)->setRotation(_seq->rotation);
			entity->getComponent<ComponentMovement>(components::COMPONENT_MOVEMENT)->setSpeed(_seq->speed);
			startingDistance = entity->getComponent<ComponentPosition>(components::COMPONENT_POSITION)->getPosition();
			std::cout << startingDistance.x << std::endl;
		}
	}
	PathSequence(){}
	~PathSequence(){}

private:
	std::vector<SeqItem>::iterator _seq;

};

