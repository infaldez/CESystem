#include "Events.h"

#include "componentDamage.h"
#include "ComponentHealth.h"

void doDamage(Entity* a, Entity* b)
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