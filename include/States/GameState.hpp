#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include "States/State.hpp"
#include "World.hpp"

class GameState : public State
{
public:
	GameState(StateStack& stack, Context context);
	virtual void draw();	
	virtual bool update(sf::Time dt);
	virtual bool handleEvent(const sf::Event& e);

private:
	World world;
};

#endif
