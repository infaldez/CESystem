#include "ActionMove.h"

#include "Entity.h"
#include "ComponentRender.h"
#include "ComponentMovement.h"
#include "MovementSystem.h"

#include <iostream>

#define SPEED 5.0f

ActionMove::ActionMove() : _dt(0)
{
}


ActionMove::~ActionMove()
{
}

void ActionMove::move(Entity* entity, std::map<sf::Keyboard::Key, actions::moveActions> inputs, bool keys[], float dt)
{
	_dt += dt;

	ComponentMovement* movement = entity->getComponent<ComponentMovement>(components::COMPONENT_MOVEMENT);
	ComponentRender* render = entity->getComponent<ComponentRender>(components::COMPONENT_RENDER);
	float rotation = 0.0f;
	float speed = 0.0f;
	float speedboost = 1.0f;
	bool actions[actions::COUNT] = { false };

	for (std::map<sf::Keyboard::Key, actions::moveActions>::iterator i = inputs.begin(); i != inputs.end(); ++i)
	{
		if (keys[i->first] == true)
			actions[i->second] = true;
	}

	if (actions[actions::CHARGE] == true)
	{
		speedboost = 3.0f;
	}
		

	if (actions[actions::MOVE_RIGHT] && !actions[actions::MOVE_LEFT]){
		rotation = 90.0f;
		speed = SPEED * speedboost;
		if (_dt >= 100) {
			render->setTilePosition(sf::Vector2u((render->getTilePosition().x + 64) % (64 * 8), 32 * 30));
			_dt = 0;
		}
	}
	if (actions[actions::MOVE_LEFT] && !actions[actions::MOVE_RIGHT]){
		rotation = 270.0f;
		speed = SPEED * speedboost;
		if (_dt >= 100) {
			render->setTilePosition(sf::Vector2u((render->getTilePosition().x + 64) % (64 * 8), 32 * 28));
			_dt = 0;
		}
	}
	if (actions[actions::MOVE_DOWN] && !actions[actions::MOVE_UP]){
		rotation = 180.0f;
		speed = SPEED * speedboost;
		if (_dt > 100){
			render->setTilePosition(sf::Vector2u((render->getTilePosition().x + 64) % (64 * 8), render->getTilePosition().y));
			_dt = 0;
		}
	}
	if (actions[actions::MOVE_UP] && !actions[actions::MOVE_DOWN]){
		rotation = 0.0f;
		speed = SPEED * speedboost;
		if (_dt > 100){
			render->setTilePosition(sf::Vector2u((render->getTilePosition().x + 64) % (64 * 8), render->getTilePosition().y));
			_dt = 0;
		}
	}
	if (actions[actions::MOVE_UP] && actions[actions::MOVE_RIGHT] && !(actions[actions::MOVE_DOWN] || actions[actions::MOVE_LEFT])){
		rotation = 45.0f;
		speed = SPEED * speedboost;
		if (_dt >= 100) {
			render->setTilePosition(sf::Vector2u((render->getTilePosition().x + 64) % (64 * 8), 32 * 30));
			_dt = 0;
		}
	}
	if (actions[actions::MOVE_RIGHT] && actions[actions::MOVE_DOWN] && !(actions[actions::MOVE_LEFT] || actions[actions::MOVE_UP])){
		rotation = 135.0f;
		speed = SPEED * speedboost;
		if (_dt >= 100) {
			render->setTilePosition(sf::Vector2u((render->getTilePosition().x + 64) % (64 * 8), 32 * 30));
			_dt = 0;
		}
	}
	if (actions[actions::MOVE_DOWN] && actions[actions::MOVE_LEFT] && !(actions[actions::MOVE_UP] || actions[actions::MOVE_RIGHT])){
		rotation = 225.0f;
		speed = SPEED * speedboost;
		if (_dt >= 100) {
			render->setTilePosition(sf::Vector2u((render->getTilePosition().x + 64) % (64 * 8), 32 * 28));
			_dt = 0;
		}
	}
	if (actions[actions::MOVE_LEFT] && actions[actions::MOVE_UP] && !(actions[actions::MOVE_RIGHT] || actions[actions::MOVE_DOWN])){
		rotation = 315.0f;
		speed = SPEED * speedboost;
		if (_dt >= 100) {
			render->setTilePosition(sf::Vector2u((render->getTilePosition().x + 64) % (64 * 8), 32 * 28));
			_dt = 0;
		}
	}
	if (actions[actions::SLASH] && actions[actions::MOVE_RIGHT]){
		//if (dt - _dt >= 100) {
			render->setTilePosition(sf::Vector2u((64 * 4), 32 * 26));
			_dt = 0;
		//}
	}
	if (actions[actions::SLASH] && actions[actions::MOVE_LEFT]){
		//if (dt - _dt >= 100) {
		render->setTilePosition(sf::Vector2u((64 * 4), 32 * 24));
		_dt = 0;
		//}
	}


	// If the player is idle
	if (speed == 0 &&  _dt > 333)
	{
		render->setTilePosition(sf::Vector2u((render->getTilePosition().x + 64) % (64 * 3), 32 * 26));
		_dt = 0;
	}

	movement->setRotation(rotation);
	movement->setSpeed(speed);
}