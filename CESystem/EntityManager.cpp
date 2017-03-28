#include "EntityManager.h"


EntityManager::EntityManager()
{
}


EntityManager::~EntityManager()
{
}

void EntityManager::add(std::unique_ptr<Entity>& Ent, bool save)
{

	_entityList.push_back(std::move(Ent));

}

void EntityManager::deleteEntities()
{
	for (std::vector<std::unique_ptr<Entity>>::iterator it = _entityList.begin(); it != _entityList.end();)
	{
		if ((*it)->componentKey[components::DELETE] == true) {
			it = _entityList.erase(it);
		}
		else { ++it; }
	}
}
