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

void DoDamage::executeCollisionEvents(Entity* a, Entity* b, std::vector<std::unique_ptr<Entity>>& entityList)
{
	if (a->componentKey[components::COMPONENT_DAMAGE] == true &&
		b->componentKey[components::COMPONENT_HEALTH] == true)
	{
		ComponentHealth* health = b->getComponent<ComponentHealth>(components::COMPONENT_HEALTH);
		componentDamage* dmg = a->getComponent<componentDamage>(components::COMPONENT_DAMAGE);

		health->setHealth(health->getHealth() - dmg->getDamage());
		//a->componentKey[components::DELETE] = true;
		if (health->getHealth() <= 0)
		{
			if (b->hasTag("player"))
			{
				b->componentKey[components::DELETE] = true;
				entityList.push_back(entitycreator::player(b->getComponent<ComponentPosition>(components::COMPONENT_POSITION)->getOriginalPosition()));
			}
			//b->componentKey[components::DELETE] = true;
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

void PathSequence::executeTimedEvent(Entity* a, float time)
{
	bool change = false;
	switch (_seq->transitionCondition)
	{
	case PathSequence::TIME:
		if (time - previousSequenceTime > _seq->transitionValue)
		{
			if (a->componentKey[components::COMPONENT_POSITION] == true)
			{
				ComponentPosition* pos = a->getComponent<ComponentPosition>(components::COMPONENT_POSITION);
				startingDistance = pos->getPosition();
			}
			change = true;
		}
		break;
	case PathSequence::X:
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
	case PathSequence::Y:
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
		
		previousSequenceTime = time;

		if (a->componentKey[components::COMPONENT_MOVEMENT] == true)
		{
			auto mov = a->getComponent<ComponentMovement>(components::COMPONENT_MOVEMENT);
			mov->setRotation(_seq->rotation);
			mov->setSpeed(_seq->speed);
		}
	}

}
