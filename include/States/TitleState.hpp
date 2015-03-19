#ifndef TITLE_STATE
#define TITLE_STATE 

#include <SFML/Graphics.hpp>
#include "States/State.hpp"
#include "States/StateStack.hpp"
#include "Resource/Resources.hpp"
#include "GUI/Button.hpp"

class TitleState : public State
{
public:
    TitleState(StateStack &stack, Context context);
    virtual void draw();
    virtual bool update(sf::Time deltaT);
    virtual bool handleEvent(const sf::Event &event);

private:
    
    TextureManager textures;
    FontManager fonts;

    sf::Sprite background;
    

    const void startGame();
    const void exitGame();
};

#endif