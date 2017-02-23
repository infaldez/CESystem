#pragma once

#include "Component.h"
#include <SFML/Graphics.hpp>

class ComponentMovement : public Component
{
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar & boost::serialization::base_object<Component>(*this);
		ar & _rotation;
		ar & _speed;
		ar & _scale.x & _scale.y;
		ar & _velocity.x & _velocity.y;
	}
private:
	float _rotation;
	float _speed;
	sf::Vector2f _scale;
	sf::Vector2f _velocity;

	void _setVelocity(float rotation, float speed);

public:
	ComponentMovement(float speed, float rotation);
	ComponentMovement(){}
	~ComponentMovement();

	void setRotation(float rotation);
	void setSpeed(float speed);
	void setVelocity(sf::Vector2f velocity);

	sf::Vector2f getVelocity();
	sf::Vector2f getScale();
	float getRotation();
	float getSpeed();
};

