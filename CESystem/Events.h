#pragma once

#include "Entity.h"
#include <boost/serialization/access.hpp>
#include <boost/serialization/base_object.hpp>
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
	virtual void executeTimedEvent(Entity* a, float time, std::vector<std::unique_ptr<Entity>>& entityList){}

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
	virtual void executeCollisionEvents(Entity* eventOwner, Entity* b, std::vector<std::unique_ptr<Entity>>& entityList);
	
	DoDamage(){}
	~DoDamage(){}
};

/*
	ADD AND FOLLOW EVENT
*/
class FollowEvent : public Event
{
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar & boost::serialization::base_object<Event>(*this);
	}
public:
	float elapsed = 0;

	virtual void executeTimedEvent(Entity* a, float time, std::vector<std::unique_ptr<Entity>>& entityList);

	FollowEvent(){}
	~FollowEvent(){}
};

class AddFollowEvent : public Event
{
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar & boost::serialization::base_object<Event>(*this);
		ar & added;
	}
public:
	bool added = false;
	virtual void executeCollisionEvents(Entity* eventOwner, Entity* b, std::vector<std::unique_ptr<Entity>>& entityList);

	AddFollowEvent(){}
	~AddFollowEvent(){}
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

class Click : public Event
{
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar & boost::serialization::base_object<Event>(*this);
	}
public:	
	std::function<void()> _lcFunc;

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
	Click(std::function<void()> lcFunc) : _lcFunc(lcFunc){}

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


/*
	SEQUENCE EVENT
*/
enum seqCondition
{
	TIME,
	X,
	Y
};

struct SeqItem
{
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar & transitionValue & rotation & speed;
		ar & transitionCondition;
	}

	float transitionValue;
	float rotation;
	float speed;
	seqCondition transitionCondition;
};

class PathSequence : public Event
{
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar & boost::serialization::base_object<Event>(*this);
		ar &  _sequence;
		ar & previousSequenceTime;
		ar & startingDistance.x & startingDistance.y;
		ar & init;
	}

public:
	bool init;
	std::vector<SeqItem> _sequence;
	float previousSequenceTime;
	sf::Vector2f startingDistance;
	virtual void executeTimedEvent(Entity* a, float time, std::vector<std::unique_ptr<Entity>>& entityList);

	PathSequence(std::vector<SeqItem> sequence, Entity* entity) : _sequence(sequence) {
		init = false;
		_seq = _sequence.begin();
		previousSequenceTime = 0;

		if (entity->componentKey[components::COMPONENT_MOVEMENT] == true && entity->componentKey[components::COMPONENT_POSITION])
		{
			// Init the entity with values from first sequence
			entity->getComponent<ComponentMovement>(components::COMPONENT_MOVEMENT)->setRotation(_seq->rotation);
			entity->getComponent<ComponentMovement>(components::COMPONENT_MOVEMENT)->setSpeed(_seq->speed);
			startingDistance = entity->getComponent<ComponentPosition>(components::COMPONENT_POSITION)->getPosition();
		}
	}
	PathSequence(){}
	~PathSequence(){}

private:
	std::vector<SeqItem>::iterator _seq;

};

