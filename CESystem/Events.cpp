#include "Events.h"

#include "componentDamage.h"
#include "ComponentHealth.h"

void causeDamage(Entity* a, Entity* b)
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

void moveBlock(std::vector<std::unique_ptr<Entity>>& entityList)
{
	for (auto& ent : entityList)
	{
		if (ent->findTag("block"))
		{
			auto cPosition = ent->getComponent<ComponentPosition>(components::COMPONENT_POSITION);
			sf::Vector2f p = cPosition->getPosition();
			cPosition->setPosition(sf::Vector2f(p.x, p.y + 1.0f));
		}
	}
}