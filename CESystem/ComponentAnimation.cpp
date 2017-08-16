#include "ComponentAnimation.h"


ComponentAnimation::ComponentAnimation(AnimData animation) 
	: Component(components::COMPONENT_ANIMATION)
{
	this->animation = animation;
}


ComponentAnimation::~ComponentAnimation()
{
}
