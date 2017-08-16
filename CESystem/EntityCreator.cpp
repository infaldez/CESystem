#include "EntityCreator.h"
#include "componentMouseInput.h"
#include "componentDamage.h"
#include "ComponentEvent.h"
#include "Events.h"
#include "ComponentHealth.h"
#include "ComponentAnimation.h"

#define TILE_SIZE 32
#define TILESET "completeSet.png"

namespace entitycreator
{

	sf::Vector2f griddedPosition(sf::Vector2f position)
	{
		return sf::Vector2f(position.x - ((int)position.x % TILE_SIZE), position.y - ((int)position.y % TILE_SIZE));
	}

	std::unique_ptr<Entity> createPassable(sf::Vector2f position, sf::Vector2u tile, int layer)
	{
		position = griddedPosition(position);
		position = griddedPosition(position);

		std::unique_ptr<Entity> entity = std::make_unique<Entity>();

		entity->addComponent(std::make_unique<ComponentRender>(TILESET, sf::Vector2u(TILE_SIZE, TILE_SIZE), tile, sf::Vector2u(TILE_SIZE, TILE_SIZE), true));
		entity->addComponent(std::make_unique<ComponentPosition>(position));

		entity->getComponent<ComponentRender>(components::COMPONENT_RENDER)->setLayer(layer);

		return std::move(entity);
	}

	std::unique_ptr<Entity> createSolid(sf::Vector2f position, sf::Vector2u tile, sf::Vector2f aabb, int layer)
	{
		position = griddedPosition(position);
		std::unique_ptr<Entity> entity = std::make_unique<Entity>();

		entity->addComponent(std::make_unique<ComponentRender>(TILESET, sf::Vector2u(TILE_SIZE, TILE_SIZE), tile, sf::Vector2u(TILE_SIZE, TILE_SIZE), true));
		entity->addComponent(std::make_unique<ComponentPosition>(position));
		entity->addComponent(std::make_unique<ComponentAABB>(aabb, sf::Vector2f(0, 0)));
		entity->addComponent(std::make_unique<ComponentCollision>(true));

		entity->getComponent<ComponentRender>(components::COMPONENT_RENDER)->setLayer(layer);

		return std::move(entity);
	}

	std::unique_ptr<Entity> createSolid(sf::Vector2f position, sf::Vector2u tilePos, int layer)
	{
		position = griddedPosition(position);
		std::unique_ptr<Entity> entity = std::make_unique<Entity>();

		entity->addComponent(std::make_unique<ComponentRender>(TILESET, sf::Vector2u(TILE_SIZE, TILE_SIZE), tilePos, sf::Vector2u(TILE_SIZE, TILE_SIZE), true));
		entity->addComponent(std::make_unique<ComponentPosition>(position));
		entity->addComponent(std::make_unique<ComponentAABB>(sf::Vector2f(TILE_SIZE, TILE_SIZE), sf::Vector2f(0, 0)));
		entity->addComponent(std::make_unique<ComponentCollision>(true));

		entity->getComponent<ComponentRender>(components::COMPONENT_RENDER)->setLayer(layer);

		return std::move(entity);
	}

	std::unique_ptr<Entity> player(sf::Vector2f position, int layer)
	{
		position = griddedPosition(position);
		std::unique_ptr<Entity> player = std::make_unique<Entity>();

		player->addComponent(std::make_unique<ComponentRender>(TILESET, sf::Vector2u(64, 64), sf::Vector2u(0, 768), sf::Vector2u(64, 64), false));
		player->addComponent(std::make_unique<ComponentPosition>(position));
		player->addComponent(std::make_unique<ComponentAABB>(sf::Vector2f(32.0, 32.0), sf::Vector2f(16.0, 32.0)));
		player->addComponent(std::make_unique<ComponentMovement>(0, 0));
		player->addComponent(std::make_unique<ComponentPlayerInput>());
		player->addComponent(std::make_unique<ComponentCollision>(true));
		player->addComponent(std::make_unique<componentMouseInput>());
		player->addComponent(std::make_unique<ComponentHealth>(10));

		player->addTag("player");

		player->getComponent<ComponentPlayerInput>(components::COMPONENT_INPUT)->setInput(sf::Keyboard::A, actions::moveActions::MOVE_LEFT);
		player->getComponent<ComponentPlayerInput>(components::COMPONENT_INPUT)->setInput(sf::Keyboard::D, actions::moveActions::MOVE_RIGHT);
		player->getComponent<ComponentPlayerInput>(components::COMPONENT_INPUT)->setInput(sf::Keyboard::W, actions::moveActions::MOVE_UP);
		player->getComponent<ComponentPlayerInput>(components::COMPONENT_INPUT)->setInput(sf::Keyboard::S, actions::moveActions::MOVE_DOWN);
		player->getComponent<ComponentPlayerInput>(components::COMPONENT_INPUT)->setInput(sf::Keyboard::LShift, actions::moveActions::CHARGE);
		player->getComponent<ComponentPlayerInput>(components::COMPONENT_INPUT)->setInput(sf::Keyboard::Space, actions::moveActions::SLASH);

		player->getComponent<ComponentRender>(components::COMPONENT_RENDER)->setLayer(layer);

		return std::move(player);
	}

	std::unique_ptr<Entity> damagewall(sf::Vector2f position, int layer)
	{
		position = griddedPosition(position);
		std::unique_ptr<Entity> entity = std::make_unique<Entity>();

		entity->addComponent(std::make_unique<ComponentRender>(TILESET, sf::Vector2u(TILE_SIZE, TILE_SIZE), sf::Vector2u(32 * 9, 32 * 17), sf::Vector2u(TILE_SIZE, TILE_SIZE), true));
		entity->addComponent(std::make_unique<ComponentPosition>(position));
		entity->addComponent(std::make_unique<ComponentAABB>(sf::Vector2f(TILE_SIZE, TILE_SIZE), sf::Vector2f(0, 0)));
		entity->addComponent(std::make_unique<ComponentCollision>(false));
		entity->addComponent(std::make_unique<ComponentMovement>(0, 0));
		entity->addComponent(std::make_unique<componentDamage>(10, false));
		entity->addComponent(std::make_unique<ComponentEvent>());
		auto e = entity->getComponent<ComponentEvent>(components::COMPONENT_EVENT);
		e->addCollisionEvent(std::make_unique<DoDamage>());
		/*SeqItem:
				float transitionValue;
				float rotation;
				float speed;
				seqCondition transitionCondition;
		*/
		std::vector<SeqItem> seq{
			{ -32, -90, 6, seqCondition::X },
			{ 32, 90, 2, seqCondition::X },
			{ 200, 180, 2, seqCondition::TIME },
			{ -32, 0, 4, seqCondition::Y }
		};
		e->addTimedEvent(std::make_unique<PathSequence>(seq, entity.get()));

		entity->getComponent<ComponentRender>(components::COMPONENT_RENDER)->setLayer(layer);

		return std::move(entity);
	}

	// ENEMY
	std::unique_ptr<Entity> enemy(sf::Vector2f position, int layer)
	{
		position = griddedPosition(position);
		std::unique_ptr<Entity> entity = std::make_unique<Entity>();

		entity->addComponent(std::make_unique<ComponentRender>(TILESET, sf::Vector2u(64, 64), sf::Vector2u(0, 768), sf::Vector2u(64, 64), false));
		entity->addComponent(std::make_unique<ComponentPosition>(position));
		entity->addComponent(std::make_unique<ComponentAABB>(sf::Vector2f(32.0, 32.0), sf::Vector2f(16.0, 32.0)));
		entity->addComponent(std::make_unique<ComponentMovement>(0, 0));
		entity->addComponent(std::make_unique<ComponentCollision>(true));
		entity->addComponent(std::make_unique<ComponentHealth>(20));
		entity->addComponent(std::make_unique<ComponentAnimation>(AnimData(std::vector<sf::Vector2f>{
			{ 0, 768 },
			{ 64, 768 },
			{ 128, 768 }

		}, 33)));

		entity->addTag("enemy");

		entity->getComponent<ComponentRender>(components::COMPONENT_RENDER)->setLayer(layer);

		return std::move(entity);
	}
}


