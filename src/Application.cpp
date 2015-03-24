#include "Application.hpp"
#include "States/GameState.hpp"
#include "States/TitleState.hpp"
#include "States/FloorEditorState.hpp"

Application::Application()
:window{{winWidth, winHeight}, "Enter the Unknown", sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize},

//Here's where resource managers get initialized
context{window, textures, fonts}, 

stateStack{context},

statsNumFrames{0}, showStats{false}
{
    //window.setFramerateLimit(60);    
    window.setVerticalSyncEnabled(true);
    registerStates();
    
    statsText.setFont(fonts[Fonts::Main]);
    statsText.setPosition(winWidth-100, 50);
    statsText.setCharacterSize(13);
    statsText.setColor(sf::Color::Green);

    //Start a new state,
    //Should be Title once it's done
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

        if (showStats) updateStats(deltaT);
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
        if (e.type == sf::Event::KeyPressed)
            if (e.key.code == sf::Keyboard::F2)
                showStats = !showStats;
    }
}

void Application::update(sf::Time deltaT)
{
    stateStack.update(deltaT);
}

void Application::updateStats(sf::Time deltaT)
{
    statsTime += deltaT;
    statsNumFrames++;

    if (statsTime > sf::seconds(1.0f))
    {
        statsText.setString("FPS: " + toString(statsNumFrames));
        statsTime -= sf::seconds(1.0f);
        statsNumFrames = 0;
    }
}

void Application::render()
{
    window.clear(sf::Color::Black);

    stateStack.draw();

    window.setView(window.getDefaultView());
    if (showStats) window.draw(statsText);
    window.display();
}

void Application::registerStates()
{
    stateStack.registerState<TitleState>(StateID::Title);
    stateStack.registerState<GameState>(StateID::Game);
    stateStack.registerState<FloorEditorState>(StateID::Editor);
}

