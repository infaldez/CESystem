#pragma once

#include "Component.h"
#include <SFML\Graphics.hpp>

// Simple helper point because serialize doesn't work with vector<sf::Vector2f>
class Point
{
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar & x & y;
	}
private:
	Point(){};
public:
	int x;
	int y;
	Point (sf::Vector2f frame)
	{
		y = frame.y;
		x = frame.x;
	}
};

class AnimData
{
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar & _animation;
		ar & _interval;
		ar & _length & _frame;
	}
private:
	std::vector<Point>::iterator _frameIt;
	std::vector<Point> _animation;
	float _interval;
	float _elapsed = 0;
	int _length = 0;
	int _frame = 0;
	Point makePoint(sf::Vector2f point){
		return Point(point);
	}
public:
	AnimData(){};
	AnimData(std::vector<sf::Vector2f> animation, float interval)
	{
		this->_interval = interval;
		setAnimation(animation);
		this->_frameIt = this->_animation.begin();
		_length = _animation.size();
	}
	~AnimData(){};

	void setAnimation(std::vector<sf::Vector2f> animation)
	{
		for (auto frame : animation)
			this->_animation.push_back(makePoint(frame));
	}

	std::vector<Point> getAnimation()
	{
		return this->_animation;
	}

	sf::Vector2u getFrame(float elapsed)
	{
		this->_elapsed += elapsed;
		if (_elapsed >= _interval)
		{
			_frame == _length -1 ? _frame = 0 : _frame++;
			_elapsed = 0;
		}
		
		return sf::Vector2u(_animation.at(_frame).x, _animation.at(_frame).y);
	}
};

class ComponentAnimation : public Component
{
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar & boost::serialization::base_object<Component>(*this);
		ar & animation;
	}
private:
	int time;
	AnimData animation;
public:
	ComponentAnimation(AnimData animation);
	ComponentAnimation(){};
	~ComponentAnimation();

	void setAnimation(AnimData animation)
	{
		this->animation = animation;
	}
	
	AnimData getAnimation()
	{
		return this->animation;
	}

	sf::Vector2u getFrame(float elapsed)
	{
		return animation.getFrame(elapsed);
	}
};

