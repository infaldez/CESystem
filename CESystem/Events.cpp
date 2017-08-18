#include "Events.h"
#include "IOmanager.h"
#include "componentDamage.h"
#include "ComponentHealth.h"
#include "ComponentText.h"
#include "states.h"
#include "Game.h"
#include "EntityCreator.h"

void Save::executeClick(Entity* a, sf::Vector2i mpos)
{
	ComponentText* text = a->getComponent<ComponentText>(components::COMPONENT_TEXT);
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
		IOmanager::save(name, *em);
		text->setText(text->getText() + "!");
	}
}

Save::Save(std::string name, EntityManager& em) : name(name), em(&em)
{

}


void DoDamage::executeCollisionEvents(Entity* eventOwner, Entity* b, std::vector<std::unique_ptr<Entity>>& entityList)
{
	/*
		GROUPS
	*/
	std::vector<std::string> allies{
		"player",
	};

	std::vector<std::string> enemies{
		"enemy"
	};

	/*
		Hits something with health
	*/
	if (eventOwner->componentKey[components::COMPONENT_DAMAGE] == true &&
		b->componentKey[components::COMPONENT_HEALTH] == true)
	{
		ComponentHealth* health = b->getComponent<ComponentHealth>(components::COMPONENT_HEALTH);
		componentDamage* dmg = eventOwner->getComponent<componentDamage>(components::COMPONENT_DAMAGE);
		
		eventOwner->componentKey[components::DELETE] = true;

		for (auto enemy : enemies)
		{
			if (b->hasTag(enemy))
			{
				health->setHealth(health->getHealth() - dmg->getDamage());
			}
		}

		for (auto ally : allies)
		{
			if (b->hasTag(ally))
				eventOwner->componentKey[components::DELETE] = false;
		}
		
		if (health->getHealth() <= 0)
		{	
			b->componentKey[components::DELETE] = true;
			if (b->hasTag("player"))
			{
				entityList.push_back(entitycreator::player(b->getComponent<ComponentPosition>(components::COMPONENT_POSITION)->getOriginalPosition()));
			}
			
		}

		if (!dmg->destroyOnImpact())
			eventOwner->componentKey[components::DELETE] = false;

	}
	/*
		Hits any solid object
	*/
	else if (eventOwner->componentKey[components::COMPONENT_DAMAGE] == true &&
		b->componentKey[components::COMPONENT_COLLISION] == true)
	{
		componentDamage* dmg = eventOwner->getComponent<componentDamage>(components::COMPONENT_DAMAGE);
		dmg->destroyOnImpact() ? eventOwner->componentKey[components::DELETE] = true : eventOwner->componentKey[components::DELETE] = false;
	}
}

void FollowEvent::executeTimedEvent(Entity* eventOwner, float time, std::vector<std::unique_ptr<Entity>>& entityList)
{
	elapsed += time;
	if (elapsed < 250)
	{
		return;
	}
		

	for (auto& ent : entityList)
	{
		if (ent->hasTag("player"))
		{
			if (ent->componentKey[components::COMPONENT_POSITION] == true &&
				eventOwner->componentKey[components::COMPONENT_POSITION] == true)
			{
				sf::Vector2f pPos = ent->getComponent<ComponentPosition>(components::COMPONENT_POSITION)->getPosition();
				sf::Vector2f ePos = eventOwner->getComponent<ComponentPosition>(components::COMPONENT_POSITION)->getPosition();

				float angle = atan2(pPos.y - ePos.y, pPos.x - ePos.x) * 180 / 3.14159265358979323846;
				int distance = sqrt(pow(pPos.x - ePos.x, 2) + pow(pPos.y - ePos.y, 2));

				if (eventOwner->componentKey[components::COMPONENT_MOVEMENT] == true)
				{
					eventOwner->getComponent<ComponentMovement>(components::COMPONENT_MOVEMENT)->setRotation(angle + 90);
					eventOwner->getComponent<ComponentMovement>(components::COMPONENT_MOVEMENT)->setSpeed(distance/25);
				}
			}
		}
	}
	elapsed = 0;
}

void AddFollowEvent::executeCollisionEvents(Entity* eventOwner, Entity* b, std::vector<std::unique_ptr<Entity>>& entityList)
{
	/*
		eventOwner = item
		b = player etc.
	*/
	if (!added && b->hasTag("player"))
	{
		added = true;
		if (eventOwner->componentKey[components::COMPONENT_EVENT] == true)
		{
			auto e = eventOwner->getComponent<ComponentEvent>(components::COMPONENT_EVENT);
			eventOwner->getComponent<ComponentCollision>(components::COMPONENT_COLLISION)->addGroup("item");
			e->addTimedEvent(std::make_unique<FollowEvent>());
		}
	}
}

void MoveBlock::executeCollisionEvents(Entity* a, Entity* b, std::vector<std::unique_ptr<Entity>>& entityList)
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

void PathSequence::executeTimedEvent(Entity* a, float time, std::vector<std::unique_ptr<Entity>>& entityList)
{

	if (!init)
	{
		_seq = _sequence.begin();
		init = true;
	}
	previousSequenceTime += time;
	bool change = false;
	switch (_seq->transitionCondition)
	{
	case seqCondition::TIME:
		if (previousSequenceTime > _seq->transitionValue)
		{
			if (a->componentKey[components::COMPONENT_POSITION] == true)
			{
				ComponentPosition* pos = a->getComponent<ComponentPosition>(components::COMPONENT_POSITION);
				startingDistance = pos->getPosition();
			}
			change = true;
		}
		break;
	case seqCondition::X:
		if (a->componentKey[components::COMPONENT_POSITION] == true)
		{
			ComponentPosition* pos = a->getComponent<ComponentPosition>(components::COMPONENT_POSITION);
			if (startingDistance.x == -1)
				startingDistance.x = pos->getPosition().x;
		
			if (_seq->transitionValue < 0 && pos->getPosition().x <= startingDistance.x + _seq->transitionValue){
				startingDistance.x += _seq->transitionValue;
				change = true;
			}
				
			if (_seq->transitionValue > 0 && pos->getPosition().x >= startingDistance.x + _seq->transitionValue){
				startingDistance.x += _seq->transitionValue;
				change = true;
			}
				
		}
		break;
	case seqCondition::Y:
		if (a->componentKey[components::COMPONENT_POSITION] == true)
		{
			ComponentPosition* pos = a->getComponent<ComponentPosition>(components::COMPONENT_POSITION);
			if (startingDistance.y == -1)
				startingDistance.y = pos->getPosition().y;

			if (_seq->transitionValue < 0 && pos->getPosition().y <= startingDistance.y + _seq->transitionValue){
				startingDistance.y += _seq->transitionValue;
				change = true;
			}

			if (_seq->transitionValue > 0 && pos->getPosition().y >= startingDistance.y + _seq->transitionValue){
				startingDistance.y += _seq->transitionValue;
				change = true;
			}

		}
		break;
	default:
		break;
	}
	

	if (change)
	{
		(_seq == _sequence.end() - 1) ? _seq = _sequence.begin() : _seq++;
		
		previousSequenceTime = 0;

		if (a->componentKey[components::COMPONENT_MOVEMENT] == true)
		{
			auto mov = a->getComponent<ComponentMovement>(components::COMPONENT_MOVEMENT);
			mov->setRotation(_seq->rotation);
			mov->setSpeed(_seq->speed);
		}
	}

}
