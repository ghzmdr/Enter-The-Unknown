#include "States/TitleState.hpp"
#include "Debug.h"

TitleState::TitleState(StateStack &stack, Context context)
: State(stack, context)
{
    log_info("Init Title State");    
    background.setTexture(textures[Textures::TitleBackground]);
}

void TitleState::draw()
{
}

bool TitleState::handleEvent(const sf::Event &event)
{
    return true;
}

bool TitleState::update(sf::Time deltaT)
{
    return true;
}

const void TitleState::startGame()
{
    requestStackPop();
    requestStackPush(StateID::Game);
}