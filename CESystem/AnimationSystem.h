#pragma once

#include "Entity.h"

class AnimationSystem
{
public:
	AnimationSystem();
	~AnimationSystem();
	void runSystem(std::vector<std::unique_ptr<Entity>>& entityList, float elapsed);
};

