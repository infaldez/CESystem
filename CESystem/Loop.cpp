#include "Loop.h"

leftCLickState LeftClick::state = NOTHING;
sf::Vector2f LeftClick::mPos = sf::Vector2f(0.0, 0.0);
sf::Vector2u LeftClick::tilePos = sf::Vector2u(0, 0);
int LeftClick::layer = 0;


Loop::Loop(sf::RenderWindow& window) : window(window)
{

}

GameState StaticGameState::gameState = GAME;