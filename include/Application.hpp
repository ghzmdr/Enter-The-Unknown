#ifndef APPLICATION_H
#define APPLICATION_H

#include <SFML/System/Time.hpp>
#include <SFML/Graphics.hpp>

#include "States/StateStack.hpp"

constexpr int winWidth{800}, winHeight{600};
const sf::Time timePerFrame{sf::seconds(1.f/60)};


class Application
{
    public:
        Application();
        void run();

    private:
        void processInput();
        void update(sf::Time deltaT);
        void render();

        void registerStates();

        bool showStats;
        sf::Text statsText;
        void updateStats(sf::Time deltaT);        
        sf::Time statsTime;
        std::size_t statsNumFrames;

        State::Context context;
        
        sf::RenderWindow window;
        TextureManager textures;
        FontManager fonts;

        StateStack stateStack;
};

#endif // APPLICATION_H
