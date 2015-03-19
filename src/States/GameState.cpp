#include "States/GameState.hpp"
#include "Debug.h"

GameState::GameState(StateStack& stack, Context context):
State(stack, context), 
world{getContext(), "./data/floors/testfloor.json"}
{
    log_info("INIT GAME STATE");
}

void GameState::draw()
{
    world.draw();
}

bool GameState::update(sf::Time dt)
{    
	world.update(dt);
	return true;
}

bool GameState::handleEvent(const sf::Event& event)
{
    world.handleEvent(event);
    return true;
}
