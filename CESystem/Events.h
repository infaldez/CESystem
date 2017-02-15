#pragma once

#include "Entity.h"
/*
	GLOBAL Event base
*/
struct Event
{
	virtual void execute(std::vector<std::unique_ptr<Entity>>& entityList){}

	virtual ~Event() {}
};


/*
	LOCAL COLLISION EVENTS
*/
void doDamage(Entity* a, Entity* b);


/*
	GLOBAL COLLISION EVENTS
*/
struct MoveBlock : public Event
{
	std::string tag;
	sf::Vector2f position;

	MoveBlock(std::string tag, sf::Vector2f position) : tag(tag), position(position) {}

	virtual void execute(std::vector<std::unique_ptr<Entity>>& entityList)
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

	~MoveBlock() {};
};