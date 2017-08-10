#pragma once

#include <functional>
#include <memory>
#include <SFML/Graphics.hpp>
#include "Loop.h"

class EditorMode : public Loop
{
public:
	void run();

	EditorMode();
	~EditorMode();
};



