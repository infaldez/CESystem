#include "AnimationSystem.h"
#include "ComponentAnimation.h"

AnimationSystem::AnimationSystem()
{
}


AnimationSystem::~AnimationSystem()
{
}


void AnimationSystem::runSystem(std::vector<std::unique_ptr<Entity>>& entityList, float elapsed)
{
	for (auto& ent : entityList)
	{
		if (ent->componentKey[components::COMPONENT_ANIMATION] == true &&
			ent->componentKey[components::COMPONENT_RENDER] == true)
		{
			auto cAnim = ent->getComponent<ComponentAnimation>(components::COMPONENT_ANIMATION);
			auto cRender = ent->getComponent<ComponentRender>(components::COMPONENT_RENDER);
			sf::Vector2u frame = cAnim->getFrame(elapsed);
			cRender->setTilePosition(frame);
		}
	}
}