#include "Application.hpp"
#include "States/GameState.hpp"
#include "States/TitleState.hpp"

Application::Application()
:window{{winWidth, winHeight}, "Tile Engine", sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize},
context{window, textures, fonts}, stateStack{context}
{
    //window.setFramerateLimit(60);    
    window.setVerticalSyncEnabled(true);
    registerStates();
    stateStack.push(StateID::Game);    
}

void Application::run()
{    
    sf::Clock clock;
    sf::Time timeSinceUpdate = sf::Time::Zero;

    while(window.isOpen())
    {
        sf::Time deltaT = clock.restart();
        timeSinceUpdate += deltaT;

        while (timeSinceUpdate > timePerFrame)
        {
            timeSinceUpdate -= timePerFrame;
            processInput();
            update(timePerFrame);

            if (stateStack.isEmpty()) window.close();
        }

        render();
    }
}

void Application::processInput()
{
    for (sf::Event e; window.pollEvent(e);)
    {
        stateStack.handleEvent(e);
        if (e.type == sf::Event::Closed)
            window.close();        
    }
}

void Application::update(sf::Time deltaT)
{
    stateStack.update(deltaT);
}

void Application::render()
{
    window.clear(sf::Color::Black);

    stateStack.draw();

    window.setView(window.getDefaultView());
    window.display();
}

void Application::registerStates()
{
    stateStack.registerState<TitleState>(StateID::Title);
    stateStack.registerState<GameState>(StateID::Game);
}

